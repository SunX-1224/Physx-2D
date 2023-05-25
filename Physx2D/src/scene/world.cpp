#include "pch.h"
#include "world.h"
#include "entity.h"
#include "../utils/time.h"

namespace Physx2D {
	World::World(Window* targetWindow) {
		this->window = targetWindow;
		this->sceneCamera = Camera();
	}

	World::~World()	{
		
		for (auto& iter : renderers) {
			iter.second.del();
		}
		renderers.clear();
		for (auto& iter : shaders) {
			if(iter.second)
				iter.second.reset();;
		}
		for (auto& ent : entities)
			delete ent;
		shaders.clear();
		renderData.clear();
	}

	void World::Initialize() {
		//defaults
		addInstancedRenderer(LINE, initVectorFromArray(LINE_VERTICES, float), 2, GL_LINES);
		addInstancedRenderer(TRIANGLE, initVectorFromArray(TRIANGLE_VERTICES, float), 3, GL_TRIANGLES);
		addInstancedRenderer(QUAD, initVectorFromArray(QUAD_VERTICES, float), 6, GL_TRIANGLES);
		addInstancedRenderer(CIRCLE, initVectorFromArray(QUAD_VERTICES, float), 6, GL_TRIANGLES);

		std::shared_ptr<Shader> s1 = std::make_shared<Shader>(Shader("res/vert.glsl", "res/quad.glsl"));
		std::shared_ptr<Shader> s2 = std::make_shared<Shader>(Shader("res/vert.glsl", "res/circle.glsl"));

		shaders[QUAD] = s1;
		shaders[CIRCLE] = s2;
		shaders[TRIANGLE] = s1;
		shaders[LINE] = s1;
	}

	void World::Update(double delta_time) {
		float time = TIME;
		handleCollisions();
		LOG_INFO("\nCollisions : %f\n", (TIME - time) * 1000.f); time = TIME;
		sceneCamera.handleInputs(window->m_window, delta_time);
		handleScriptUpdate(delta_time);
		LOG_INFO("Script Update : %f\n", (TIME - time) * 1000.f); time = TIME;
		handlePhysics(delta_time);
		LOG_INFO("Physics Update : %f\n", (TIME - time) * 1000.f); time = TIME;
		updateRenderData();
		LOG_INFO("RenderData update : %f\n", (TIME - time) * 1000.f); time = TIME;
	}

	void World::Render() {
		for (auto& iter : renderers) {
			if (textures[iter.first] != nullptr) {
				textures[iter.first]->bind();
				textures[iter.first]->texUnit(shaders[iter.first].get(), "u_texture");
			}
			iter.second.Draw(shaders[iter.first].get());
		}
	}

	Entity* World::CreateEntity(std::string name) {
		EntityID id = manager.CreateEntity();
		Entity* ent =new Entity(id, this);

		ent->AddComponent<Transform>();
		ent->AddComponent<Tag>(name.empty()?"Entity":name);

		entities.push_back(ent);
		return ent;
	}

	void World::loadShader(const char* vert, const char* frag, uint32_t ID) {
		shaders[ID] = std::make_shared<Shader>(Shader(vert, frag));
	}

	void World::loadTexture(const char* path, const char* type, uint32_t ID, uint32_t slot) {
		textures[ID] = std::make_shared<Texture>(Texture(path, type, slot));
	}

	InstancedRenderer* World::addInstancedRenderer(uint32_t type, std::vector<float> vertices, uint32_t numPoints,GLenum draw_mode) {
		bool createNew = true;
		for (auto& iter : renderers) {
			if (iter.first == type) {
				createNew = false;
				break;
			}
		}
		if (not createNew) { 
			LOG_WARN("Renderer of the type %u already exists", type);
			return &renderers[type];
		}

		renderers[type] = InstancedRenderer(vertices, numPoints, draw_mode);
		renderers[type].VertexDataLayout(0, 2, GL_FLOAT, 2*sizeof(vec2), 0);					//vec2 vertex position
		renderers[type].VertexDataLayout(1, 2, GL_FLOAT, 2*sizeof(vec2), sizeof(vec2));			//vec2 texture coords

		renderers[type].InstanceLayout(2, 2, GL_FLOAT, sizeof(RenderData), 0);					//vec2 position
		renderers[type].InstanceLayout(3, 2, GL_FLOAT, sizeof(RenderData), 2 * sizeof(float));	//vec2 scale
		renderers[type].InstanceLayout(4, 1, GL_FLOAT, sizeof(RenderData), 4 * sizeof(float));	//float rotation
		renderers[type].InstanceLayout(5, 4, GL_FLOAT, sizeof(RenderData), 5 * sizeof(float));	//vec4 color
		renderers[type].InstanceLayout(6, 2, GL_FLOAT, sizeof(RenderData), 9 * sizeof(float));	//texOffset
		renderers[type].InstanceLayout(7, 2, GL_FLOAT, sizeof(RenderData), 11 * sizeof(float)); //Tiling factor

		return &renderers[type];
	}

	InstancedRenderer* World::addInstancedRenderer(uint32_t type, std::vector<float> vertices, std::vector<uint32_t> indices, GLenum draw_mode) {
		bool createNew = true;
		for (auto& iter : renderers) {
			if (iter.first == type) {
				createNew = false;
				break;
			}
		}
		if (not createNew) {
			LOG_WARN("Renderer of the type %u already exists", type);
			return &renderers[type];
		}
		renderers[type] = InstancedRenderer(vertices, indices, draw_mode);
		renderers[type].VertexDataLayout(0, 2, GL_FLOAT, 2*sizeof(vec2), 0);						//vec2 vertex position
		renderers[type].VertexDataLayout(1, 2, GL_FLOAT, 2*sizeof(vec2), sizeof(vec2));			//vec2 texture coords

		renderers[type].InstanceLayout(2, 2, GL_FLOAT, sizeof(RenderData), 0);					//vec2 position
		renderers[type].InstanceLayout(3, 2, GL_FLOAT, sizeof(RenderData), 2 * sizeof(float));	//vec2 scale
		renderers[type].InstanceLayout(4, 1, GL_FLOAT, sizeof(RenderData), 4 * sizeof(float));	//float rotation
		renderers[type].InstanceLayout(5, 4, GL_FLOAT, sizeof(RenderData), 5 * sizeof(float));	//vec4 color
		renderers[type].InstanceLayout(6, 2, GL_FLOAT, sizeof(RenderData), 9 * sizeof(float));	//texOffset
		renderers[type].InstanceLayout(7, 2, GL_FLOAT, sizeof(RenderData), 11 * sizeof(float)); //Tiling factor
		
		return &renderers[type];
	}

	void World::handleScriptUpdate(float delta_time) {
		for (auto& entity : entities) {
			if (entity->HasComponent<ScriptComponent>()) {
				entity->GetComponent<ScriptComponent>()->script->update(delta_time);
			}
		}
	}

	void World::handlePhysics(double delta_time) {
		for (auto& entity : entities) {
			if (entity->HasComponent<RigidBody2D>()) {
				PhysicsHandler::updateRigidBody(entity->GetComponent<RigidBody2D>(), entity->GetComponent<Transform>(), delta_time);
			}
		}
	}

	void World::handleCollisions() {
		centerRect treesize = centerRect(vec2(0.f), window->GetResolution());
		vec2 range(10.f, 10.f);
		
		QuadTree<Entity*> qtree(treesize);
		
		//populate quadtree
		for (auto& entity : entities) {
			if (entity->HasComponent<Collider>()) {
				Transform* tfr = entity->GetComponent<Transform>();
				Collider* cld = entity->GetComponent<Collider>();

				if (cld->typeIndex == std::type_index(typeid(AABB)) || cld->typeIndex == std::type_index(typeid(BoundingCircle)))
					continue;
				
				range.x = max(range.x, cld->getSize().x);
				range.y = max(range.y, cld->getSize().y);
				qtree.insert(tfr->Position + cld->Offset, entity);
			}
		}
		range *= 2.f;

		//collision check 
		for (auto& entity : entities) {
			if (entity->HasComponent<Collider>()) {
				Transform* tfr = entity->GetComponent<Transform>();
				Collider* cld = entity->GetComponent<Collider>();

				std::vector<Entity*> neighbours;

				bool isBound = (cld->typeIndex == std::type_index(typeid(AABB))) || (cld->typeIndex == std::type_index(typeid(BoundingCircle)));

				qtree.query(centerRect(tfr->Position + cld->Offset, isBound?cld->getSize()+range : range), neighbours);

				for (auto& nent : neighbours) {
					if (nent == entity) continue;
					
					Transform* ntfr = nent->GetComponent<Transform>();
					Collider* ncld = nent->GetComponent<Collider>();

					RigidBody2D* nrgb = nullptr;
					RigidBody2D* rgb = nullptr;

					if(entity->HasComponent<RigidBody2D>())
						rgb = entity->GetComponent<RigidBody2D>();
					if (nent->HasComponent<RigidBody2D>()) 
						nrgb = nent->GetComponent<RigidBody2D>();

					BodyType type1 = rgb ? rgb->Type : STATIC;
					BodyType type2 = nrgb ? nrgb->Type : KINETIC;

					CollisionData data = PhysicsHandler::checkCollision(cld, tfr, type1, ncld, ntfr, type2);
					if (data.status) {
						if (type1 == KINETIC)
							PhysicsHandler::collisionPhysics(data, rgb, nrgb);
						else if (type2 == KINETIC && nrgb)
							PhysicsHandler::collisionPhysics(data, nrgb, rgb);

						if (entity->HasComponent<ScriptComponent>()) {
							entity->GetComponent<ScriptComponent>()->script->OnCollisionDetected(data, nent);
						}
					}
				}
			}
		}
	}

	void World::updateRenderData() {
		for (auto& vec : renderData)
			vec.second.clear();

		for (auto& entity : entities) {
			if (entity->HasComponent<SpriteRenderer>()) {
				Transform* trnf = entity->GetComponent<Transform>();
				SpriteRenderer* rnc = entity->GetComponent<SpriteRenderer>();
				renderData[rnc->type].push_back(RenderData(*trnf, rnc->color, rnc->offset, rnc->tiling)); // TODO : can be optimized
			}
		}

		for (auto& iter : shaders) {
			iter.second->use();
			sceneCamera.setValues(iter.second.get(), window->GetResolution());
			//iter.second->setFloat("u_time", glfwGetTime());
		}
		
		for (auto& renderer : renderers) {
			auto& rd = renderData[renderer.first];
			if (rd.size() == 0) continue;
			renderer.second.InstanceData(rd.data(), rd.size(), sizeof(RenderData));
		}
	}
}

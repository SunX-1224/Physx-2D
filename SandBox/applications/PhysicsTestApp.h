#pragma once

#include <physx2d.h>

using namespace Physx2D;

class Gravity : public ScriptObject {
	public:
    vec2 gravity = vec2(0.f, -600.f);
    float timer= 0.0f;

		virtual void setup() {

		}
		virtual void update(float delta_time) {
			self->GetComponent<RigidBody2D>()->Acceleration = -self->GetComponent<Transform>()->Position * 5.0f;
			//self->GetComponent<RigidBody2D>()->Acceleration = gravity;
      timer+= delta_time;

      //if(timer > 5.f) {
      //  gravity.y  = -gravity.y;
      //  gravity.x = Math::randomr_f(-10.f, 10.f);
      //  timer = 0.f;
      //}

		}

		virtual void OnCollisionDetected(CollisionData& data, Entity* other) {
			self->GetComponent<SpriteRenderer>()->color *= Color(1.3f, 1.f, 1.f, 1.f);
		}

};

class PhysicsTestApp : public Application {
public:
	World* world;

	PhysicsTestApp(uint32_t num_obj = 1200) {
		world = new World(m_window);
		world->loadDefaultRenderer();
		world->loadDefaultRenderer(CIRCLE);
		world->loadShader("res/shaders/vert.glsl", "res/shaders/circle.glsl", CIRCLE);

		Random rng(0xfafafafa);
		for (uint32_t i = 0; i < num_obj; i++) {
			Entity* ent = world->CreateEntity();
			float sc = rng.randr_f(8.f, 16.f);
			ent->AddComponent<SpriteRenderer>(CIRCLE, Color(.5f, rng.rand_f(), 0.6f, 1.f), vec2(0.f), vec2(1.f));
			ent->AddComponent<CircleCollider>(vec2(), sc*0.6f);
			ent->AddComponent<RigidBody2D>(KINETIC, vec2(0.f, 0.f), 0.f, 1.f, 0.1f, 0.95f);
			ent->AddComponent<ScriptComponent>(new Gravity());

			Transform* tfr = ent->GetComponent<Transform>();
			tfr->Position = vec2(rng.randr_i(-400, 400), rng.randr_i(-300, 300));
			tfr->Scale = vec2(sc);
		}
		Entity* ent = world->CreateEntity();
		auto __res = m_window->GetResolution();
		ent->AddComponent<AABB>(0.f, vec2(__res.x, __res.y));
		ent->GetComponent<Transform>()->Scale = vec2(__res.x, __res.y);
		ent->AddComponent<SpriteRenderer>(QUAD, .3f);
	}

	virtual void Run() override {
		Time time;
		time.initTimer();

		while (!m_window->ShouldClose()) {
			world->Update(time.get_delta_time());
			m_window->FillScreen(Color(0.1f, 0.2f, 0.1f, 1.f));
			world->Render();
			m_window->OnUpdate();
			time.update();
			m_window->SetTitle((std::to_string(time.get_fps())).c_str());
		}
	}

	~PhysicsTestApp() {
		delete world;
	}
};

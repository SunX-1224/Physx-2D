#pragma once

#include <physx2d.h>

using namespace Physx2D;

class PhysicsTestApp : public Application {
public:
	World* world;

	PhysicsTestApp(uint32_t num_obj) {
		world = new World(m_window);
		world->loadDefaultRenderer();
		world->loadDefaultRenderer(CIRCLE);
		world->loadShader("res/shaders/vert.glsl", "res/shaders/circle.glsl", CIRCLE);

		Random rng(0xfafafafa);
		for (uint32_t i = 0; i < num_obj; i++) {
			Entity* ent = world->CreateEntity();
			float sc = rng.randr_f(20.f, 40.f);
			ent->AddComponent<SpriteRenderer>(CIRCLE, Color(.5f, rng.rand_f(), 0.6f, 1.f), vec2(0.f), vec2(1.f));
			ent->AddComponent<CircleCollider>(vec2(), sc*0.5f);
			ent->AddComponent<RigidBody2D>(KINETIC, vec2(rng.randr_i(-30, 30), rng.randr_i(-30, 30)));

			Transform* tfr = ent->GetComponent<Transform>();
			tfr->Position = vec2(rng.randr_i(-400, 400), rng.randr_i(-300, 300));
			tfr->Scale = vec2(sc);
		}
		Entity* ent = world->CreateEntity();
		ent->AddComponent<AABB>(0.f, vec2(1400, 800));
		ent->GetComponent<Transform>()->Scale = vec2(1400, 800);
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

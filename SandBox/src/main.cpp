#include "boids/boid.h"
#include "core/entry.h"

using namespace Physx2D;

class SandBox :public Application {

public:
	Window* window;
	World* world;

	SandBox() {
		window = new Window();
		window->Init();

		world = new World(window);
		
		//bounds
		{
			Entity* entity = world->CreateEntity();
			Transform* tfr = entity->GetComponent<Transform>();
			tfr->Scale = window->GetResolution();
			entity->AddComponent<AABB>(vec2(), tfr->Scale);
			entity->AddComponent<RigidBody2D>();
			entity->AddComponent<SpriteRenderer>(QUAD, Color(0.7f));
		}
		
		Entity* entity = world->CreateEntity(std::string("entity"));
		entity->AddComponent<ScriptComponent>(new Boid(5));

		world->Initialize();
	}
	~SandBox() {
		delete world;
		delete window;
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		while (!window->ShouldClose()) {
			window->UpdateEvents();

			world->Update(clock.get_delta_time());

			window->FillScreen(Color(0.05f, 0.05f, 0.05f, 1.f));
			world->Render();
			
			window->Update();
			clock.update();
			window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
		window->Destroy();
	}
};


Physx2D::Application* Physx2D::CreateApplication() {
	return new SandBox();
}

#include "boids/boid.h"
#include "core/entry.h"

using namespace Physx2D;

class SandBox :public Application {

public:
	std::unique_ptr<World> world;

	SandBox() {
		world = std::unique_ptr<World>(new World(m_window.get()));
		
		Entity* entity = world->CreateEntity(std::string("entity"));
		entity->AddComponent<ScriptComponent>(new Boid(2000));
				
		world->Initialize();
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		while (!m_window->ShouldClose()) {
			world->Update(clock.get_delta_time());

			m_window->FillScreen(Color(0.05f, 0.05f, 0.05f, 1.f));
			world->Render();
			
			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};


Physx2D::Application* Physx2D::CreateApplication() {
	return new SandBox();
}

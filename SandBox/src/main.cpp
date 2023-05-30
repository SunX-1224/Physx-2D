#include "compute_shader_test/ray_tracing.h"
#include "core/entry.h"

using namespace Physx2D;

class SandBox :public Application {

public:
	std::unique_ptr<World> world;

	SandBox() {
		/*world = std::unique_ptr<World>(new World(m_window.get()));
		Entity* ent = world->CreateEntity();
		ent->AddComponent<ScriptComponent>(new Boid(2000));

		world->Initialize();*/
	}

	virtual void Run() override {
		ray_tracing rtx(m_window->GetResolution());

		Time clock;
		clock.initTimer();

		rtx.setup();
		while (!m_window->ShouldClose()) {
			//world->Update(clock.get_delta_time());

			//rtx.compute->use();
			//rtx.compute->setFloat("u_time", clock.get_time());
			rtx.dispatch();
			m_window->FillScreen(Color(0.f, 0.f, 0.f, 1.f));
			rtx.render();
			
			//world->Render();
			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};


Physx2D::Application* Physx2D::CreateApplication() {
	return new SandBox();
}

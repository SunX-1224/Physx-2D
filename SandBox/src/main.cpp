//#include "cellular_automata/mnca.h"
#include "cellular_automata/CA_gpu.h"
//#include "boids/boid.h"
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
		//LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();
		
		//mnca ca("res/c_shaders/mnca.glsl", "res/images/reactionState.png", "res/images/neighborhoods/mitosis", 4);
		CA_gpu ca("res/c_shaders/gameoflife.glsl", "res/images/reactionState.png");
		ca.setup();
		while (!m_window->ShouldClose()) {
			//world->Update(clock.get_delta_time());
			ca.update();

			m_window->FillScreen(Color(0.f, 0.f, 0.f, 1.f));

			ca.draw();
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

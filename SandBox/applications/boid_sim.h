#pragma once

#include "../src/boids/boid.h"

class BoidSimulationApp : public Application {
public:
	std::unique_ptr<World> world;

	BoidSimulationApp() {
		world = std::unique_ptr<World>(new World(m_window));
		Entity* ent = world->CreateEntity();
		ent->AddComponent<ScriptComponent>(new Boid(1200, m_window->GetResolution()));

		world->loadDefaultRenderer(TRIANGLE);

		LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		while (!m_window->ShouldClose()) {
			world->Update(clock.get_delta_time());

			m_window->FillScreen(Color(0.f, 0.f, 0.f, 1.f));

			world->Render();
			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};
/**/

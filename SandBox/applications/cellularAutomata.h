#pragma once

#include "../src/cellular_automata/CA_gpu.h"


class CellularAutomataApp : public Application {
 public:
	CellularAutomataApp() {
		LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		//CA_gpu ca("res/c_shaders/wolfram.glsl", "res/images/test.png");
		CA_gpu ca("res/c_shaders/reaction.glsl", "res/images/test.png");
		//CA_gpu ca("res/c_shaders/b_reaction.glsl", "res/images/test.png");
		//CA_gpu ca("res/c_shaders/gameoflife.glsl", "res/images/test.png");
		ca.setup();
		while (!m_window->ShouldClose()) {

			ca.update();
			m_window->FillScreen(Color(0.f, 0.f, 0.f, 1.f));
			
			ca.draw();

			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};
/**/

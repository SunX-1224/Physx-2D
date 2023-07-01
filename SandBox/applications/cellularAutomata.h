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

		//CA_gpu ca("res/c_shaders/wolfram.glsl", "res/images/wolfram.png");
		//CA_gpu ca("res/c_shaders/reaction.glsl", "res/images/battle_fs.png");
		//CA_gpu ca("res/c_shaders/b_reaction.glsl", "res/images/battle_fs.png");
		CA_gpu ca("res/c_shaders/gameoflife.glsl", "res/images/battle_fs.png");
		ca.setup();
		float _t = clock.get_time();
		bool _s = false;
		while (!m_window->ShouldClose()) {

			if (_s) ca.update();
			else _s = (clock.get_time() - _t) > 6.f;
			//m_window->FillScreen(Color(0.f, 0.f, 0.f, 1.f));
			
			ca.draw();

			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};
/**/
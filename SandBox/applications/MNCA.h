#pragma once
#include "../src/cellular_automata/mnca.h"

class MNCA_App : public Application {
public:

	MNCA_App() {
		LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		mnca ca("res/c_shaders/mnca.glsl", "res/images/test.png", "res/images/neighborhoods/mitosis", 4);
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
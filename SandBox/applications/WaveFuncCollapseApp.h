#pragma once

#include "../src/wavefcollapse/WFC.h"

class WaveFuncCollapseApp : public Application {
public:
	std::unique_ptr<World> world;

	WaveFuncCollapseApp() {
		world = std::unique_ptr<World>(new World(m_window.get()));
		world->loadTexture("res/images/textures/test.png", "wfc", DEFAULT);

		generateLevel();

		world->loadDefaultRenderer();
		LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	void generateLevel() {
		// for output
		vec2 tilesize(0.33f, 0.5f);

		//for WFC algo
		ivec2 gridsize(12, 12);
		std::vector<int> def_states = { 0,1,2,3,4 };
		std::map<ivec2, std::vector<int>> init_states;
		std::map<ivec2, int> fin_states;
		std::map<int, std::vector<int>> rules;
		{//assigning rules
			rules[0] = {};
			rules[1] = {};
			rules[2] = {};
			rules[3] = {};
			rules[4] = {};
		}
		WaveFuncCollapse gen(gridsize, rules, init_states, def_states);

		gen.collapse();
		gen.getFinalState(fin_states);

		//generate output after collapse
		for (int y = 0; y < gridsize.y; y++) {
			for (int x = 0; x < gridsize.x; x++) {
				Entity* ent = world->CreateEntity();
				Transform* tfr = ent->GetComponent<Transform>();
				
				tfr->Scale = vec2(50, 50);
				tfr->Position = vec2((x-gridsize.x/2)*tfr->Scale.x, (y-gridsize.y/2)*tfr->Scale.y);
				
				ent->AddComponent<SpriteRenderer>(
					DEFAULT, 
					vec4(1.f), 
					offset_from_ind(fin_states[ivec2(x,y)], ivec2(3, 2)),
					tilesize
				);
			}
		}
	}

	vec2 offset_from_ind(int i, ivec2 tilegrd) {
		return vec2(float(i % tilegrd.x) / tilegrd.x, float(i / tilegrd.y) / tilegrd.y);
	}

	virtual void Run() override {
		Time clock;
		clock.initTimer();

		while (!m_window->ShouldClose()) {
			world->Update(clock.get_delta_time());

			m_window->FillScreen(Color(0.2f, 0.2f, 0.2f, 1.f));

			world->Render();
			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
	}
};
/**/

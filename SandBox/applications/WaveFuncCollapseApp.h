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
		vec2 tilesize(1.f/3.f, 0.5f);

		//for WFC algo
		ivec2 gridsize(50, 40);
		std::vector<int> def_states = {0,1,2,4,5};
		std::map<ivec2, Tile> init_states;
		for (int y = 0; y < gridsize.y; y++) {
			for (int x = 0; x < gridsize.x; x++) {
				init_states[ivec2(x, y)] = { false, def_states};
			}
		}

		std::map<int, std::vector<int>[4]> rules;
		{//assigning rules, dir_index : d = 0, l = 1, u = 2, r = 3
			rules[0][0] = {1, 4, 5};
			rules[0][1] = {4, 5};
			rules[0][2] = {2, 5};
			rules[0][3] = {1, 5};

			rules[1][0] = {1, 4, 5};
			rules[1][1] = {0, 4, 5};
			rules[1][2] = {0, 4};
			rules[1][3] = {2, 4};

			rules[2][0] = {0, 2};
			rules[2][1] = {1, 2};
			rules[2][2] = {2, 5};
			rules[2][3] = {2, 4};

			rules[4][0] = {1, 4, 5};
			rules[4][1] = {1, 2};
			rules[4][2] = {0, 1, 4};
			rules[4][3] = {0, 1, 5};

			rules[5][0] = {0, 2};
			rules[5][1] = {0, 4, 5};
			rules[5][2] = {0, 1, 4};
			rules[5][3] = {0, 1, 5};
		}
		WaveFuncCollapse gen(gridsize, rules, init_states);
		gen.collapse();

		std::map<ivec2, int> fin_states;
		gen.getFinalState(fin_states);

		//generate output after collapse
		for (int y = 0; y < gridsize.y; y++) {
			for (int x = 0; x < gridsize.x; x++) {
				Entity* ent = world->CreateEntity();
				Transform* tfr = ent->GetComponent<Transform>();
				
				tfr->Scale = vec2(50, 50);
				tfr->Position = vec2((x-gridsize.x/2)*(tfr->Scale.x+2.f), (y-gridsize.y/2)*(tfr->Scale.y+2.f));
				
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
		return vec2(float(i % tilegrd.x) / tilegrd.x, float(i / tilegrd.x) / tilegrd.y);
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

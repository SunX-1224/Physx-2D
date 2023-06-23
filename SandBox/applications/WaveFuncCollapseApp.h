#pragma once

#include "../src/wavefcollapse/WFC.h"

class WaveFuncCollapseApp : public Application {
public:
	World* world;
	WaveFuncCollapse* wfc;
	std::map<ivec2, Entity*> entities;
	std::map<ivec2, int> fin_states;

	WaveFuncCollapseApp() {
		world = new World(m_window.get());
		world->loadTexture("res/images/textures/test.png", "wfc", DEFAULT);

		initwfc();

		world->loadDefaultRenderer();
		LOG_INFO("%d, %d\n", m_window->GetWidth(), m_window->GetHeight());
	}

	~WaveFuncCollapseApp() {
		LOG_INFO("Destructor called%c", '\n');
	}

	void initwfc() {
		// for output
		vec2 tilesize(1.f/3.f, 0.5f);

		//for WFC algo
		ivec2 gridsize(40, 30);
		std::vector<int> def_states = {2,0,1,4,5};
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
		wfc = new WaveFuncCollapse(gridsize, rules, init_states);
		//gen.collapse();

		wfc->getFinalState(fin_states);

		//generate output after collapse
		for (int y = 0; y < gridsize.y; y++) {
			for (int x = 0; x < gridsize.x; x++) {
				Entity* ent = world->CreateEntity();
				entities[ivec2(x, y)] = ent;

				Transform* tfr = ent->GetComponent<Transform>();
				
				tfr->Scale = vec2(30, 30);
				//tfr->Position = vec2((x-gridsize.x/2)*tfr->Scale.x, (y-gridsize.y/2)*tfr->Scale.y);
				tfr->Position = vec2((x-gridsize.x/2)*(tfr->Scale.x+2.f), (y-gridsize.y/2)*(tfr->Scale.y+2.f));
				
				ent->AddComponent<SpriteRenderer>(
					DEFAULT, 
					vec4(1.f), 
					offset_from_ind(fin_states[ivec2(x, y)], ivec2(3, 2)),
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

			ivec2 lst = wfc->lowest_entropy();
			if (lst.x >= 0) {
				wfc->collapse_tile(lst);
				wfc->getFinalState(fin_states);
				entities[lst]->GetComponent<SpriteRenderer>()->offset = offset_from_ind(fin_states[lst], ivec2(3, 2));
			}
			world->Update(clock.get_delta_time());

			m_window->FillScreen(Color(0.2f, 0.2f, 0.2f, 1.f));

			world->Render();
			m_window->OnUpdate();
			clock.update();
			m_window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}

		delete world;
		delete wfc;
	}
};
/**/

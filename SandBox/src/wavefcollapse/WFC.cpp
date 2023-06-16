#include "WFC.h"

WaveFuncCollapse::WaveFuncCollapse(
    ivec2 gridsize,
    std::map<int, std::vector<int>> rls,
    std::map<ivec2, std::vector<int>>& init_states, 
    std::vector<int> default_state
)
    : gridsize(gridsize), def_states(default_state), rules(rls)
{
    for (int y = 0; y < gridsize.y; y++) {
        for (int x = 0; x < gridsize.x; x++) {
            ivec2 position(x, y);
            if (init_states.count(position) > 0) {
                std::vector<int>& states = init_states[position];
                if (states.size() > 1)
                    uncollapsed[position] = states;
                else if (states.size() == 1)
                    collapsed[position] = states[0];
                else
                    uncollapsed[position] = def_states;
            }
            else {
                uncollapsed[position] = def_states;
            }
        }
    }
}

WaveFuncCollapse::~WaveFuncCollapse() {

}

void WaveFuncCollapse::collapse() {
	for (int y = 0; y < gridsize.y; y++) {
		for (int x = 0; x < gridsize.x; x++) {
            // TODO : Collapse correctly

            collapsed[ivec2(x, y)] = rng.randr_i(0, 6);
		}
	}
}

void WaveFuncCollapse::getFinalState(std::map<ivec2, int>& states) {
	states = collapsed;
}

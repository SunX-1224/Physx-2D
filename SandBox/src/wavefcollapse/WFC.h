#pragma once
#include <physx2d.h>

using namespace Physx2D;

class WaveFuncCollapse {
public:
	ivec2 gridsize;
		
	std::map<int, std::vector<int>> rules;
	std::map<ivec2, std::vector<int>> uncollapsed;
	std::map<ivec2, int> collapsed;
	std::vector<int> def_states;
	Random rng = Random(0xfafafafa);

	WaveFuncCollapse(
		ivec2 gridsize,
		std::map<int, std::vector<int>> rules,
		std::map<ivec2, std::vector<int>>& init_state, 
		std::vector<int> def_state
	);
	~WaveFuncCollapse();

	void collapse();
	void getFinalState(std::map<ivec2, int>& states);
};

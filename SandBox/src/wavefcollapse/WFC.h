#pragma once
#include <physx2d.h>

using namespace Physx2D;

typedef struct {
	bool collapsed;
	std::vector<int> states;
} Tile;


class WaveFuncCollapse {
public:
	ivec2 gridsize;
		
	std::map<int, std::vector<int>[4]> rules;
	std::map<ivec2, Tile> tiles;
	Random rng = Random(0xaaaaaaaa);

	WaveFuncCollapse(
		ivec2 gridsize,
		std::map<int, std::vector<int>[4]> rules,
		std::map<ivec2, Tile> init_states
	);
	~WaveFuncCollapse();

	void collapse();
	void getFinalState(std::map<ivec2, int>& states);
	
private:
	ivec2 lowest_entropy();
	void collapse_tile(ivec2 tile);
	void filterState(std::vector<int> &trgStates, int state, int dir);
	bool in(std::vector<int> trg, int val);
};

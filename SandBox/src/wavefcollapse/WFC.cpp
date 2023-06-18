#include "WFC.h"

WaveFuncCollapse::WaveFuncCollapse(
    ivec2 gridsize,
    std::map<int, std::vector<int>[4]> rls,
    std::map<ivec2, Tile> init_states
)
    : gridsize(gridsize), tiles(init_states), rules(rls)
{
    
}

WaveFuncCollapse::~WaveFuncCollapse() {

}

void WaveFuncCollapse::getFinalState(std::map<ivec2, int>& states) {
    for (int y = 0; y < gridsize.y; y++) {
        for (int x = 0; x < gridsize.x; x++) {
            ivec2 pos(x, y);
            states[pos] = tiles[pos].states[0];
        }
    }
}

void WaveFuncCollapse::collapse() {
    ivec2 lwst(-1);
    for (int i = 0; i < gridsize.x * gridsize.y; i++) {
        lwst = lowest_entropy();
        if (lwst.x < 0) break;
        collapse_tile(lwst);
    }
}

ivec2 WaveFuncCollapse::lowest_entropy() {
    ivec2 lwst(-1);
    for (int y = 0; y < gridsize.y; y++) {
        for (int x = 0; x < gridsize.x; x++) {
            ivec2 pos(x, y);

            if (!tiles[pos].collapsed) {
                if (lwst.x < 0) lwst = pos;
                else if (tiles[pos].states.size() < tiles[lwst].states.size()) lwst = pos;
            }
        }
    }
    return lwst;
}

void WaveFuncCollapse::collapse_tile(ivec2 pos) {
    tiles[pos].collapsed = true;
    
    int rni = rng.randr_i(0, tiles[pos].states.size());
    int ns = tiles[pos].states[rni];
    tiles[pos].states.clear();
    tiles[pos].states.push_back(ns);
    
    // TODO : update neighbour after collapse
    //follow rules, dir_index : d = 0, l = 1, u = 2, r = 3

    for (int i = 0; i < 4; i++) {
        ivec2 npos = ivec2(i%2 * ((i/2)*2 - 1), (i+1)%2 * ((i+1)/2*2 - 1)) + pos;
        if (npos.x >= gridsize.x || npos.y >= gridsize.y) continue;
           
        filterState(tiles[npos].states, ns, i);
    }
}


void WaveFuncCollapse::filterState(std::vector<int>& states, int state, int dir) {
    std::vector<int> tstates = states;

    states.clear();

    for (auto& st : tstates) {
        if (in(rules[state][dir], st)) {
            states.push_back(st);
        }
    }
    if (states.size() == 0) states.push_back(rng.randr_i(0, 6));
}

bool WaveFuncCollapse::in(std::vector<int> trg, int val)
{
    bool xx = false;
    for (auto& i : trg) {
        xx |= i == val;
        if (xx) break;
    }
    return xx;
}

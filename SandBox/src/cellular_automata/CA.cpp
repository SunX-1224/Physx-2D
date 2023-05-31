#include "CA.h"

CA::CA(uint32_t w_cells, uint32_t h_cells, vec2 _size) : cell_size(_size),m_width(w_cells), m_height(h_cells) {

	prev_states = new bool* [w_cells];
	states = new bool* [w_cells];
	cells = new Entity* *[w_cells];

	for (int x = 0; x < m_width; x++) {
		
		cells[x] = new Entity * [h_cells];
		states[x] = new bool[h_cells];
		prev_states[x] = new bool[w_cells];
	}
}

void CA::setup() {
	
	//cells position assigning
	vec2 pos(-0.5f*(int)m_width, 0);
	for (int x = 0; x < m_width; x++) {
		pos.y = -0.5f * (int)m_height;
		for (int y = 0; y < m_height; y++) {
			prev_states[x][y] = Math::random_f(x*y) < 0.05f;
			cells[x][y] = self->m_world->CreateEntity();
			cells[x][y]->AddComponent<SpriteRenderer>(QUAD, Color(prev_states[x][y]));
			Transform* tfr = cells[x][y]->GetComponent<Transform>();

			pos.y++;
			tfr->Scale = cell_size;
			tfr->Position = pos * cell_size;			
		}
		pos.x ++;
	}
}

void CA::update(float delta_time) {
	for (int x = 0; x < m_width; x++) {
		for (int y = 0; y < m_height; y++) {

			update_cell(x, y);
			if (states[x][y] != prev_states[x][y]) {
				cells[x][y]->GetComponent<SpriteRenderer>()->color = Color(states[x][y]);
				prev_states[x][y] = states[x][y];
			}
		}
	}
}

inline void CA::update_cell(int x, int y) {
	int n = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (x == 0 && y == 0) continue;
			if (prev_states[(x + i) % m_width][(y + j) % m_height]) n += 1;
		}
	}

	if (n >= 4 || n <= 1)
		states[x][y] = 0;
	else if (n == 3)
		states[x][y] = 1;
	else
		states[x][y] = prev_states[x][y];
}

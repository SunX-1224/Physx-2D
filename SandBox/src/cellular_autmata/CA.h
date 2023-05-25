#pragma once
#include "physx2d.h"

using namespace Physx2D;

class CA : public ScriptObject {

	public:
		Entity*** cells;
		bool** states;
		bool** prev_states;
		vec2 cell_size;
		uint32_t m_width, m_height;

		CA(uint32_t w_cells, uint32_t h_cells, vec2 size);

		virtual void setup() override;
		virtual void update(float delta_time) override;
		inline void update_cell(int x, int y);
};


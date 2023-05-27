#pragma once
#include "physx2d.h"

using namespace Physx2D;
class CA_fb {
	public:
		
		Shader* shader = nullptr;

		CA_fb(vec2 res, Shader* shader);
		~CA_fb();

		void update();

		void draw();
};


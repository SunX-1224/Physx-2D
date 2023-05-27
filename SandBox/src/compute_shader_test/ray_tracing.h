#pragma once
#include "physx2d.h"

using namespace Physx2D;

class ray_tracing {
	public:
		vec2 res;
		Texture* texture;
		ComputeShader* compute;
		Renderer2D* renderer;
		Shader* shader;

		ray_tracing(vec2 _res = vec2(1024, 1024));
		~ray_tracing();

		void dispatch();
		void render();

};


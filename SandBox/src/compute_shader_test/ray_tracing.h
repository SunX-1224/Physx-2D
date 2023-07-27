#pragma once
#include "physx2d.h"

using namespace Physx2D;

using ivec3 = tvec3<int>;


struct RayCastMat {
	vec4 color;
	vec4 e_color_strength;
};
struct Sphere {
	vec4 pos_rad;
	RayCastMat material;
};

class ray_tracing {
	public:
		vec2 res;
		Texture* texture;
		ComputeShader* compute;
		Renderer2D* renderer;
		Shader* shader;
		Buffer* buffer;

		ray_tracing(vec2 _res = vec2(1024, 1024));
		~ray_tracing();

		void setup(uint32_t size = 10);
		void dispatch();
		void render();

};


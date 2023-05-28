#pragma once
#include "physx2d.h"

using namespace Physx2D;

struct RayCastMat {
	Color color;
};
struct Sphere {
	vec3<float> position;
	float radius;
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


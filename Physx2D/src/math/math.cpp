#include "math.h"

namespace Physx2D{

	const double Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
	const float Math::MAX_float = 3.40282e+038f;
	const float Math::MIN_float = -3.40282e+038f;

	float Math::dot(vec2 u, vec2 v){
		return (u.x * v.x + u.y * v.y);
	}

	mat3 Math::get_ortho2d(vec2 center, vec2 area) {
		vec2 btm_left = center - area * 0.5f;
		vec2 top_right = center + area * 0.5f;

		mat3 ortho = mat3(1.0f);
		ortho.value[0][0] = 2.0f / (top_right.x - btm_left.x);
		ortho.value[1][1] = 2.0f / (top_right.y - btm_left.y);

		ortho.value[0][2] = - (btm_left.x + top_right.x)/(btm_left.x - top_right.x);
		ortho.value[1][2] = - (btm_left.y + top_right.y)/(btm_left.y - top_right.y);
		return ortho;
	}

	mat3 Math::get_view2d(vec2 pos) {
		mat3 view = mat3(1.0f);
		view.value[0][2] = -pos.x;
		view.value[1][2] = -pos.y;
		return view;
	}

	float Math::random(uint32_t seed) {
		seed ^= seed << 17;
		seed ^= seed >> 23;
		seed ^= seed << 5;
		float rn = (float)seed / 0xffffffff;
		return rn;
	}
	int Math::randint(int a, int b){
		float x = (random(a) + random(b) + random(glfwGetTime() * 10000000))/3.f;
		return a + (int)(x * (b - a));
	}
}
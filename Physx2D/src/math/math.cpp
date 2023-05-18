#include "math.h"

namespace Physx2D{

	const double Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
	const float Math::MAX_float = 3.40282e+038f;
	const float Math::MIN_float = -3.40282e+038f;

	float Math::dot(vec2 u, vec2 v){
		return (u.x * v.x + u.y * v.y);
	}

	mat3 Math::get_ortho2d(vec2 btm_left, vec2 top_right) {
		mat3 ortho = mat3(1.0f);
		ortho.value[0][0] = 2.0f / (top_right.x - btm_left.x);
		ortho.value[1][1] = 2.0f / (top_right.y - btm_left.y);

		ortho.value[0][2] = -1.0f;
		ortho.value[1][2] = -1.0f;
		return ortho;
	}

	float Math::random(uint32_t seed) {
		uint32_t r = seed *seed* 637432847 + 748357345;
		r *= r + 78457834;
		r *= (glfwGetTime() * 1000000000);
		float rn = (float)r / 0xffffffff;
		return rn;
	}
	int Math::randint(int a, int b){
		float x = (random(a) + random(b) + random(glfwGetTime() * 1000000))/3.f;
		return a + (int)(x * (b - a));
	}
}
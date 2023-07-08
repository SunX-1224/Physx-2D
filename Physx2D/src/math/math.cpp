#include "pch.h"
#include "math.h"

namespace Physx2D {

	const double Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

	inline float Math::dot(tvec2<int> u, tvec2<int> b) {
		return u.x * b.x + u.y * b.y;
	}

	inline float Math::dot(tvec2<float> u, tvec2<float> b) {
		return u.x * b.x + u.y * b.y;
	}

	inline mat3 Math::get_ortho2d(vec2 center, vec2 area) {
		vec2 b_l = center - area * 0.5f;
		vec2 t_r = center + area * 0.5f;

		return {
			{2.0f / (t_r.x - b_l.x), 0.f, 0.f},
			{0.f, 2.0f / (t_r.y - b_l.y), 0.f},
			{ -(b_l.x + t_r.x) / (b_l.x - t_r.x),   -(b_l.y + t_r.y) / (b_l.y - t_r.y), 1.f}
		};
	}

	inline mat3 Math::get_view2d(tvec2<float> pos) {
		return {
			{1.f, 0.f, 0.f},
			{0.f, 1.f, 0.f},
			{-pos.x, -pos.y,1.f}
		};
	}

	inline float Math::random_i(uint32_t seed)
	{
		seed = seed * 747796405 + 2891336453;
		uint32_t result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
		result = (result >> 22) ^ result;

		return result;
	}

	inline float Math::random_f(uint32_t seed) {
		return random_i(seed) / 0xffffffff;
	}

	inline int Math::randomr_i(int a, int b) {
		float x = (random_f(a) + random_f(b)) / 2.f;
		return a + (int)(x * (b - a));
	}

	inline float Math::randomr_f(float a, float b)
	{
		float x = (random_f(a * 1000) + random_f(b * 2000)) / 2.f;
		return a + x * (b - a);
	}
	
	inline bool centerRect::contains(tvec2<float> point)
	{
		return point.x > (x - w * 0.5f) && point.x<(x + w * 0.5f) && point.y >(y - h * 0.5f) && point.y < (h * 0.5f + y);
	}

	inline bool centerRect::intersects(centerRect n)
	{
		return abs(x - n.x) < ((w + n.w) * 0.5f) && abs(y - n.y) < ((h + n.h) * 0.5f);
	}

	inline centerRect centerRect::getPart(float xp, float yp)
	{
		return centerRect(x + xp * 0.5f * w, y + yp * 0.5f * h, abs(xp) * w, abs(yp) * h);
	}

	Random::Random(uint32_t seed) : seed_i(seed), seed_f(seed) {}

	inline uint32_t Random::rand_i()
	{
		return Math::random_i(seed_i++);
	}

	inline int Random::randr_i(int a, int b)
	{
		return a + Math::random_f(seed_i++) * (b - a);
	}

	inline float Random::rand_f()
	{
		return Math::random_f(seed_f++);
	}

	inline float Random::randr_f(float a, float b)
	{
		return a + Math::random_f(seed_f++) * (b - a);
	}

	mat3 mat3::operator+(mat3 u) {
		return {
			{_0[0] + u[0][0],_0[1] + u[0][1],_0[2] + u[0][2]},
			{_1[0] + u[1][0],_1[1] + u[1][1],_1[2] + u[1][2]},
			{_2[0] + u[2][0],_2[1] + u[2][1],_2[2] + u[2][2]}
		};
	}

	mat3 mat3::operator-(mat3 u) {
		return mat3{
			{_0[0] - u[0][0],_0[1] - u[0][1],_0[2] - u[0][2]},
			{_1[0] - u[1][0],_1[1] - u[1][1],_1[2] - u[1][2]},
			{_2[0] - u[2][0],_2[1] - u[2][1],_2[2] - u[2][2]}
		};
	}

	mat3 mat3::operator*(mat3 u)
	{
		mat3 res;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++) {
					res[i][j] += (*this)[i][k] * u[k][j];
				}
			}
		}
		return res;
	}

	mat3 mat3::operator*(float x)
	{
		mat3 _;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				_[i][j] =(*this)[i][j] * x;
			}
		}
		return _;
	}
	
	mat3 mat3::operator/(float x)
	{
		mat3 _;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				_[i][j] = (*this)[i][j]/x;
			}
		}
		return _;
	}

	float* mat3::operator[](int i) {
		return (float*) this + 3*i;
	}

	template class PHYSX2D_API tvec2<int>;
	template class PHYSX2D_API tvec2<float>;

	template class PHYSX2D_API tvec3<int>;
	template class PHYSX2D_API tvec3<float>;

	template class PHYSX2D_API tvec4<int>;
	template class PHYSX2D_API tvec4<float>;
}

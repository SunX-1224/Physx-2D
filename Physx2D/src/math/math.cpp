#include "pch.h"
#include "math.h"

namespace Physx2D {

	const double Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
	const float Math::MAX_float = 3.40282e+038f;
	const float Math::MIN_float = -3.40282e+038f;

	inline float Math::dot(vec2 u, vec2 v) {
		return (u.x * v.x + u.y * v.y);
	}

	mat3 Math::get_ortho2d(vec2 center, vec2 area) {
		vec2 btm_left = center - area * 0.5f;
		vec2 top_right = center + area * 0.5f;

		mat3 ortho = mat3(1.0f);
		ortho.value[0][0] = 2.0f / (top_right.x - btm_left.x);
		ortho.value[1][1] = 2.0f / (top_right.y - btm_left.y);

		ortho.value[0][2] = -(btm_left.x + top_right.x) / (btm_left.x - top_right.x);
		ortho.value[1][2] = -(btm_left.y + top_right.y) / (btm_left.y - top_right.y);
		return ortho;
	}

	mat3 Math::get_view2d(vec2 pos) {
		mat3 view = mat3(1.0f);
		view.value[0][2] = -pos.x;
		view.value[1][2] = -pos.y;
		return view;
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

	inline vec2 vec2::normalized()
	{
		return this->length() > 1e-6f ? (*this) * vec2(1.f / this->length()) : vec2(0.0f);
	}

	inline float vec2::length() {
		return sqrt(x * x + y * y);
	}
	vec2 vec2::rotate(float a)
	{
		float c = cos(a);
		float s = sin(a);
		vec2 n(0.f);
		n.x = x * c - y * s;
		n.y = x * s + y * c;
		return n;
	}
	vec2 vec2::operator=(vec2 v)
	{
		x = v.x;
		y = v.y;
		return v;
	}
	vec2 vec2::operator-()
	{
		return vec2(-x, -y);
	}
	vec2 vec2::operator+(vec2 v)
	{
		return vec2(x + v.x, y + v.y);
	}
	void vec2::operator+=(vec2 v)
	{
		x = x + v.x;
		y = y + v.y;
	}
	vec2 vec2::operator-(vec2 v)
	{
		return vec2(x - v.x, y - v.y);
	}
	void vec2::operator-=(vec2 v)
	{
		x -= v.x;
		y -= v.y;
	}
	vec2 vec2::operator*(vec2 v)
	{
		return vec2(x * v.x, y * v.y);
	}
	void vec2::operator*=(vec2 a)
	{
		x *= a.x;
		y *= a.y;
	}
	vec4 vec4::operator+(vec4 v)
	{
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	void vec4::operator+=(vec4 v)
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
	}
	vec4 vec4::operator-(vec4 v)
	{
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	void vec4::operator-=(vec4 v)
	{
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
	}
	vec4 vec4::operator*(vec4 v)
	{
		return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	void vec4::operator*=(vec4 a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
		w *= a.w;
	}
	inline bool centerRect::contains(vec2 point)
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

	template class PHYSX2D_API tvec3<int>;
	template class PHYSX2D_API tvec3<float>;
}
#pragma once
#include "pch.h"
#include "core/core.h"

namespace Physx2D {

	struct PHYSX2D_API vec2 {
		float x;
		float y;

		vec2(float a = 0.0f) : x(a), y(a) {}
		vec2(float _x, float _y): x(_x), y(_y) {}

		inline vec2 normalized();
		inline float length();
		vec2 rotate(float a);

		vec2 operator =(vec2 v);
		vec2 operator -();
		vec2 operator +(vec2 v);
		void operator +=(vec2 v);
		vec2 operator -(vec2 v);
		void operator -=(vec2 v);
		vec2 operator *(vec2 v);
		void operator *= (vec2 a);
	};

	struct PHYSX2D_API vec4 {
		float x;
		float y;
		float z;
		float w;

		vec4(float a = 0.0f) : x(a), y(a), z(a), w(a) {}
		vec4(float _x, float _y, float _z, float _w) :x(_x), y(_y), z(_z), w(_w) {}

		vec4 operator +(vec4 v);
		void operator +=(vec4 v);
		vec4 operator -(vec4 v);
		void operator -=(vec4 v);
		vec4 operator *(vec4 v);
		void operator *= (vec4 a);
	};

	struct PHYSX2D_API centerRect {
		float x;
		float y;
		float w;
		float h;

		centerRect(float x_, float y_, float w_, float h_) :x(x_), y(y_), w(w_), h(h_) {}
		centerRect(vec2 cen, vec2 res) :x(cen.x), y(cen.y), w(res.x), h(res.y) {}

		inline bool contains(vec2 point);

		inline bool intersects(centerRect n);

		inline centerRect getPart(float xp, float yp);
	};		
		
	struct PHYSX2D_API mat3 {
			float value[3][3];

			mat3(float x = 0.0f) :value{ {x, 0.f, 0.f}, {0.f, x, 0.f}, {0.f, 0.f, x} } {}
		};

	class PHYSX2D_API Random {
		public:
			Random(uint32_t seed);

			inline uint32_t rand_i();
			inline int randr_i(int a, int b);

			inline float rand_f();
			inline float randr_f(float a, float b);

		private:
			uint32_t seed_i;
			uint32_t seed_f;
	};

	class PHYSX2D_API Math {
	public:
		static const double PI;
		static const float MAX_float;
		static const float MIN_float;

		static inline float dot(vec2 u, vec2 b);
		static mat3 get_ortho2d(vec2 center, vec2 area);
		static mat3 get_view2d(vec2 pos);
		
		static inline float random_i(uint32_t seed);
		static inline float random_f(uint32_t seed);
		
		static inline int randomr_i(int a, int b);
		static inline float randomr_f(float a, float b);
	};
}
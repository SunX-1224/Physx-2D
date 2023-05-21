#pragma once

#include "..\core\core.h"
#include<math.h>
#include<iostream>
#include "../utils/time.h"

namespace Physx2D {

	struct PHYSX2D_API vec2 {
		float x;
		float y;

		vec2(float a = 0.0f) {
			x = a;
			y = a;
		}
		vec2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		vec2 normalized() {
			return this->length()>0.00001f?(*this) * vec2(1.f/this->length()):vec2(0.0f);
		}
		float length() {
			return sqrt(x * x + y * y);
		}
		vec2 rotate(float a) {
			float c = cos(a);
			float s = sin(a);
			vec2 n(0.f);
			n.x = x * c - y * s;
			n.y = x * s + y * c;
			return n;
		}

		vec2 operator =(vec2 v) {
			x = v.x;
			y = v.y;
			return v;
		}
		vec2 operator -() {
			return vec2(-x, -y);
		}
		vec2 operator +(vec2 v) {
			return vec2(x + v.x, y + v.y);
		}
		void operator +=(vec2 v) {
			x = x + v.x;
			y = y + v.y;
		}
		vec2 operator -(vec2 v) {
			return vec2(x - v.x, y - v.y);
		}
		void operator -=(vec2 v) {
			x -= v.x;
			y -= v.y;
		}
		vec2 operator *(vec2 v) {
			return vec2(x * v.x, y * v.y);
		}
		void operator *= (vec2 a) {
			x *= a.x;
			y *= a.y;
		}
	};

	struct PHYSX2D_API vec4 {
		float x;
		float y;
		float z;
		float w;

		vec4(float a = 0.0f) {
			x = a;
			y = a;
			z = a;
			w = a;
		}
		vec4(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		vec4 operator +(vec4 v) {
			return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		void operator +=(vec4 v) {
			x += v.x; y += v.y; z += v.z; w += v.w;
		}
		vec4 operator -(vec4 v) {
			return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		void operator -=(vec4 v) {
			x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		}
		vec4 operator *(vec4 v) {
			return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		void operator *= (vec4 a) {
			x *= a.x;
			y *= a.y;
			z *= a.z;
			w *= a.w;
		}
	};

	struct PHYSX2D_API centerRect {
		float x;
		float y;
		float w;
		float h;

		centerRect(float x_, float y_, float w_, float h_) :x(x_), y(y_), w(w_), h(h_) {}
		centerRect(vec2 cen, vec2 res) :x(cen.x), y(cen.y), w(res.x), h(res.y) {}

		bool contains(vec2 point) {
			return point.x > (x - w * 0.5f) && point.x<(x + w * 0.5f) && point.y > (y - h * 0.5f) && point.y < (h * 0.5f + y);
		}

		bool intersects(centerRect n) {
			return abs(x - n.x) < ((w + n.w) * 0.5f) && abs(y - n.y) < ((h + n.h) * 0.5f);
		}

		centerRect getPart(float xp, float yp) {
			return centerRect(x + xp * 0.5f * w, y + yp * 0.5f * h, abs(xp) * w, abs(yp)*h);
		}
	};		
		
	struct PHYSX2D_API mat3 {
			float value[3][3];

			mat3(float x = 0.0f) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						value[i][j] = i == j ? x : 0.0f;
					}
				}
			}
		};

	class PHYSX2D_API Math {
	public:
		static const double PI;
		static const float MAX_float;
		static const float MIN_float;

		static float dot(vec2 u, vec2 b);
		static mat3 get_ortho2d(vec2 center, vec2 area);
		static mat3 get_view2d(vec2 pos);

		static float random(uint32_t seed);
		static int randint(int a, int b);
	};
}
#pragma once

#include <GLFW/glfw3.h>
#include "../math/math.h"
#include <vector>
#include "../core/core.h"

#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 800
#define TIME glfwGetTime()
#define arrayLength(a) (sizeof(a)/sizeof(a[0]))
#define initVectorFromArray(arr, type) std::vector<type>(arr, arr + arrayLength(arr))
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)

namespace Physx2D {
	typedef vec4 Color;

	const vec2 QUAD_VERTICES[6]{
			vec2(-.5f, -.5f),
			vec2( .5f, -.5f),
			vec2(-.5f,  .5f),

			vec2( .5f, -.5f),
			vec2(-.5f,  .5f),
			vec2( .5f,  .5f)
	};

	const vec2 UNIT_RECT[4]{
			vec2(-.5f, -.5f),
			vec2( .5f, -.5f),
			vec2( .5f,  .5f),
			vec2(-.5f,  .5f),
	};

	const vec2 TRIANGLE_VERTICES[3] {
		vec2(-0.866f, -0.5f),
		vec2( 0.866f, -0.5f),
		vec2( 0.000f,  1.0f)
	};

	const vec2 LINE_VERTICES[2]{
		vec2(0.f),
		vec2(1.0f, 0.f)
	};

	struct PHYSX2D_API WindowProps {
		uint32_t WIDTH, HEIGHT;
		bool RESIZABLE, FULLSCREEN_MODE;
		const char* TITLE;

		WindowProps(
			uint32_t width = SCREEN_WIDTH,
			uint32_t height = SCREEN_HEIGHT,
			const char* title = "Physx2D Window",
			bool resizable = true,
			bool fullscreen = false
		) {
			WIDTH = width;
			HEIGHT = height;
			TITLE = title;
			RESIZABLE = resizable;
			FULLSCREEN_MODE = fullscreen;
		}
	};

	struct PHYSX2D_API CollisionData {
		bool status;
		vec2 axis;

		CollisionData(bool status = false, vec2 axis = vec2(0.f)) {
			this->status = status;
			this->axis = axis;
		}
	};
}
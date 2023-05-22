#pragma once

#include "../core/core.h"
#include <GLFW/glfw3.h>

#define TIME glfwGetTime()

namespace Physx2D {
	class PHYSX2D_API Time {
		public:
			double current_time, last_time;

			Time();

			inline void initTimer();
			inline double get_time();
			inline int get_fps();
			inline double get_delta_time();
			inline void update();
	};
}

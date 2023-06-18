#pragma once

/*
	Time/Clock related functions...
		> initTimer : resets/initializes the timer
		> get_time : returns the duration passed since timer has been initialized
		> get_fps : returns the fps when in loop
		> get_delta_time : returns the time elapsed between frames in loop
		> update : updates the values in loop
*/

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

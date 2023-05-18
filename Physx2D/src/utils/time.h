#pragma once
#include <GLFW/glfw3.h>
#include "../core/core.h"

namespace Physx2D {
	class PHYSX2D_API Time {
		public:
			double current_time, last_time;

			Time();

			void initTimer();
			double get_time();
			int get_fps();
			double get_delta_time();
			void update();
	};
}

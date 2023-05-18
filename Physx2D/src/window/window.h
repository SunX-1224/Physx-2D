#pragma once
#include "../core/core.h"

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../math/math.h"
#include "../utils/defaults.h"

namespace Physx2D{
	class PHYSX2D_API Window {
		public:
			GLFWwindow* m_window;
			WindowProps properties;
			uint32_t VERSION_MAJOR, VERSION_MINOR;

			Window(
				WindowProps props = WindowProps(),
				uint32_t version_major = 4,
				uint32_t version_minor = 6
			);

			void Init();
			bool ShouldClose();
			void SetClose(bool value);
			vec2 GetResolution();
			void FillScreen(Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
			void SetTitle(const char* title);
			void UpdateEvents();
			void Update();
			void Destroy();
	};
}

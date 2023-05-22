#pragma once

#include<glad/glad.h>
#include <GLFW/glfw3.h>
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
			inline bool ShouldClose();
			inline void SetClose(bool value);
			inline vec2 GetResolution();
			inline void FillScreen(Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
			inline void SetTitle(const char* title);
			inline void UpdateEvents();
			inline void Update();
			inline void Destroy();
	};
}

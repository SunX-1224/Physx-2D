#pragma once

/*
	Handles the window creation, update, resize, etc and also has some getter functions for window
*/

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "../utils/defaults.h"

namespace Physx2D{
	
	class PHYSX2D_API Window {
		public:
			GLFWwindow* m_window;
			static WindowProps properties;
			uint32_t VERSION_MAJOR, VERSION_MINOR;

			Window(
				WindowProps props = WindowProps(),
				uint32_t gl_version_major = 4,
				uint32_t gl_version_minor = 6
			);
			~Window();
			void OnInit();
			inline void SetVsync(bool value);
			inline bool ShouldClose();
			inline void SetClose(bool value);
			inline ivec2 GetResolution() const;
			inline int GetWidth() const;
			inline int GetHeight() const;
			inline void FillScreen(Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
			inline void SetTitle(const char* title);
			inline void OnUpdate();
	};
}

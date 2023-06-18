#pragma once

/*
	Handles the window creation, update, resize, etc and also has some getter functions for window
*/

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "../utils/defaults.h"

namespace Physx2D{
	
	inline PHYSX2D_API void  GetError();
	
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
			~Window();
			void OnInit();
			inline void SetVsync(bool value);
			inline bool ShouldClose();
			inline void SetClose(bool value);
			inline ivec2 GetResolution();
			inline int GetWidth();
			inline int GetHeight();
			inline void FillScreen(Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
			inline void SetTitle(const char* title);
			inline void OnUpdate();
			
	};
}

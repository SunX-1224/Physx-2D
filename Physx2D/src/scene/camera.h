#pragma once

/*
	Camera is not fully implemented. Currently only zooming is allowed, there is no movement for the camera till now
	
	TODO : 
		> Camera movement
		> Bug fixes
*/

#include "../renderer/shader.h"
#include "../math/math.h"
#include <GLFW/glfw3.h>

namespace Physx2D {
	class PHYSX2D_API Camera {

		public:
			vec2 position;
			float fov = 1.0f;
			float sensitivity = 0.1f;

			vec2 speed = vec2(100.f, 100.f);

			Camera(vec2 position = vec2(), float fov = 1.0f);

			mat3 get_matrices(vec2 res);
			void setValues(Shader* shader, vec2 res);
			void handleInputs(GLFWwindow* window, float delta_time);
	};
}
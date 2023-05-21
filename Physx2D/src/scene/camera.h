#pragma once
#include "../renderer/shader.h"
#include "../math/math.h"

namespace Physx2D {

	class PHYSX2D_API Camera {

		public:
			vec2 position;
			vec2 view_area;
			float fov = 1.0f;
			float sensitivity = 0.1f;

			vec2 speed = vec2(100.f, 100.f);

			Camera(vec2 position = vec2(), vec2 view_area = vec2(800, 800));

			mat3 get_matrices();
			void setValues(Shader* shader);
			void handleInputs(GLFWwindow* window, float delta_time);
	};
}
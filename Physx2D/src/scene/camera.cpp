#include "camera.h"
#include "../core/Log.h"

namespace Physx2D {
	Camera::Camera(vec2 position, float fov) {
		this->position = position;
		this->fov = fov;
	}

	mat3 Camera::get_matrices(vec2 res) {
		mat3 mat = Math::get_ortho2d(vec2(), res * fov);
		mat.value[0][2] += -mat.value[0][0] * position.x;
		mat.value[1][2] += -mat.value[1][1] * position.y;
		return mat;
	}

	void Camera::setValues(Shader* shader, vec2 res) {
		shader->setFloat("u_fov", fov);
		shader->setMat3("u_camMatrices", get_matrices(res));
		shader->setVec2("u_resolution", res);
	}

	void Camera::handleInputs(GLFWwindow* window, float delta_time) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		// TODO : camera movement
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			position.y += speed.y * delta_time;

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			position.y -= speed.y * delta_time;

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			position.x -= speed.x * delta_time;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			position.x += speed.x * delta_time;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			position = vec2();

		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && fov < 5.f )
			fov += delta_time * sensitivity;

		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS&& fov > 0.2f)
			fov -= delta_time * sensitivity;
	}
}
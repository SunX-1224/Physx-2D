#pragma once
#include <physx2d.h>

using namespace Physx2D;
class CA_gpu{
	public:
		uint32_t w, h;
		Texture *cur = nullptr, *prev = nullptr;
		ComputeShader* compute;
		Renderer2D* renderer;
		Shader* shader;

		CA_gpu(const char* compute_shader, const char* initial_state_texture);
		~CA_gpu();

		void setup();
		void update();
		void draw();
};


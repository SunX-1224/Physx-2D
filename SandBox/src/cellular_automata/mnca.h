#pragma once
#include <physx2d.h>

using namespace Physx2D;

class mnca {
	public:
		uint32_t w, h;
		Texture* cur = nullptr, * prev = nullptr;
		std::vector<Texture*> neighbours;
		ComputeShader* compute;
		Renderer2D* renderer;
		Shader* shader;

		mnca(const char* compute_shader, const char* initial_state_texture, std::string nh_dir, int count);
		~mnca();

		void setup();
		void update();
		void draw();
};


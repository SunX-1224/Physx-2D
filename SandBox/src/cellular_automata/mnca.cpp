#include "mnca.h"

mnca::mnca(const char* compute_shader, const char* instate_path, std::string nh_dir, int count) {
	cur = new Texture(instate_path, "ca", 0, GL_UNSIGNED_BYTE, GL_RGBA32F);
	prev = new Texture(instate_path, "ca", 1, GL_UNSIGNED_BYTE, GL_RGBA32F);

	w = prev->m_width;
	h = prev->m_height;

	for (int i = 0; i < count; i++) {
		Texture* tex = new Texture((nh_dir + "/nh" + std::to_string(i + 1) + ".png").c_str(), "nh", i + 2, GL_UNSIGNED_BYTE, GL_R8);
		neighbours.push_back(tex);
	}

	shader = new Shader("res/shaders/f_vert.glsl", "res/shaders/f_frag.glsl");

	compute = new ComputeShader(compute_shader);

	auto __data = initVectorFromArray(FRAME_QUAD, float);
	renderer = new Renderer2D(__data, 6, GL_TRIANGLES);
	renderer->VertexDataLayout(0, 2, GL_FLOAT, 2 * sizeof(vec2), 0);
	renderer->VertexDataLayout(1, 2, GL_FLOAT, 2 * sizeof(vec2), sizeof(vec2));
}

mnca::~mnca() {
	cur->del();
	prev->del();
	shader->del();
	renderer->del();

	delete cur;
	delete prev;
	delete shader;
	delete renderer;
	delete compute;

	for (int i = 0; i < neighbours.size(); i++) {
		neighbours[i]->del();
		delete neighbours[i];
	}
}

void mnca::setup() {

	for (auto& tex : neighbours) {
		tex->bindImageTextureMode(GL_READ_ONLY, GL_R8);
	}
	compute->use();
}

void mnca::update() {
	prev->bindImageTextureMode(GL_READ_WRITE, GL_RGBA32F, 0);
	cur->bindImageTextureMode(GL_READ_WRITE, GL_RGBA32F, 1);
	compute->dispatch(w / 16, h / 16);
}

void mnca::draw() {
	compute->waitUntilFinish(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	cur->texUnit(shader, "tex");
	cur->bind();
	renderer->Draw(shader);

	std::swap<Texture*>(cur, prev);
}



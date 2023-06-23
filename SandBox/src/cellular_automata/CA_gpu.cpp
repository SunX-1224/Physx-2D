#include "CA_gpu.h"

CA_gpu::CA_gpu(const char* compute_shader, const char* instate_path) {
	cur = new Texture(instate_path, "ca", 0, GL_UNSIGNED_BYTE, GL_RGBA32F);
	prev = new Texture(instate_path, "ca", 1, GL_UNSIGNED_BYTE, GL_RGBA32F);
	
	w = prev->m_width;
	h = prev->m_height;

	shader = new Shader("res/shaders/f_vert.glsl", "res/shaders/f_frag.glsl");
	
	compute = new ComputeShader(compute_shader);

	std::vector<float> __verts = initVectorFromArray(FRAME_QUAD, float);
	renderer = new Renderer2D(__verts, 6, GL_TRIANGLES);
	renderer->VertexDataLayout(0, 2, GL_FLOAT, 2 * sizeof(vec2), 0);
	renderer->VertexDataLayout(1, 2, GL_FLOAT, 2 * sizeof(vec2), sizeof(vec2));
}

CA_gpu::~CA_gpu() {
	cur->del();
	prev->del();
	shader->del();
	renderer->del();

	delete cur;
	delete prev;
	delete shader;
	delete renderer;
	delete compute;
}

void CA_gpu::setup() {
	compute->use();
}

void CA_gpu::update() {
	prev->bindImageTextureMode(GL_READ_WRITE, GL_RGBA32F, 0);
	cur->bindImageTextureMode(GL_READ_WRITE, GL_RGBA32F, 1);
	compute->dispatch(w/16, h/16);
}

void CA_gpu::draw() {
	compute->waitUntilFinish(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	cur->texUnit(shader, "tex");
	cur->bind();
	renderer->Draw(shader);
	
	std::swap<Texture*>(cur, prev);
}
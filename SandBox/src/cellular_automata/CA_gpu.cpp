#include "CA_gpu.h"

CA_gpu::CA_gpu() {
	cur = new Texture("res/images/test.png", "ca", 0, GL_UNSIGNED_BYTE, GL_R8);
	prev = new Texture("res/images/test.png", "ca", 1, GL_UNSIGNED_BYTE, GL_R8);
	
	w = prev->m_width;
	h = prev->m_height;

	shader = new Shader("res/shaders/f_vert.glsl", "res/shaders/f_frag.glsl");
	
	compute = new ComputeShader("res/c_shaders/gameoflife.glsl");

	renderer = new Renderer2D(initVectorFromArray(FRAME_QUAD, float), 6, GL_TRIANGLES);
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
	prev->bindImageTextureMode(GL_READ_WRITE, GL_R8, 0);
	cur->bindImageTextureMode(GL_READ_WRITE, GL_R8, 1);
	cur->bind();
	prev->bind();
	compute->dispatch(w, h);
}

void CA_gpu::draw() {
	compute->waitUntilFinish(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	cur->texUnit(shader, "tex");
	cur->bind();
	renderer->Draw(shader);
	
	std::swap<Texture*>(cur, prev);
}
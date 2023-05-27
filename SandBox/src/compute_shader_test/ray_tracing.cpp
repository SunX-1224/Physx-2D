#include "ray_tracing.h"

ray_tracing::ray_tracing(vec2 _res) : res(_res) {
	
	compute = new ComputeShader("res/c_shaders/ray_trace.glsl");

	texture = new Texture(NULL, "rtx", 0, res.x, res.y, GL_FLOAT, GL_RGBA32F);
	texture->bindImageTextureMode(GL_WRITE_ONLY, GL_RGBA32F);

	shader = new Shader("res/shaders/f_vert.glsl", "res/shaders/f_frag.glsl");

	renderer = new Renderer2D(initVectorFromArray(FRAME_QUAD, float), 6, GL_TRIANGLES);
	renderer->VertexDataLayout(0, 2, GL_FLOAT, 2 * sizeof(vec2), 0);
	renderer->VertexDataLayout(1, 2, GL_FLOAT, 2 * sizeof(vec2), sizeof(vec2));

	vec3<int> t = compute->getWorkGrpCount();
	LOG_INFO("WG_count : %d, %d, %d\n", t.x, t.y, t.z);
	t = compute->getWorkGrpSize();
	LOG_INFO("WG_size : %d, %d, %d\n", t.x, t.y, t.z);
	LOG_INFO("WG_max_invocations : %d\n", compute->maxLocalWorkGrpInv());
}

ray_tracing::~ray_tracing() {
	texture->del();
	delete texture;
	shader->del();
	delete shader;
	renderer->del();
	delete renderer;
	delete compute;
}

void ray_tracing::dispatch()
{
	texture->bind();
	compute->dispatch(res.x/10, res.y/5);
}

void ray_tracing::render() {
	compute->waitUntilFinish(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	
	texture->texUnit(shader, "tex");
	texture->bind();
	renderer->Draw(shader);
}


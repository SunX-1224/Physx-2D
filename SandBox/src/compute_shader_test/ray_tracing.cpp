#include "ray_tracing.h"

ray_tracing::ray_tracing(vec2 _res) : res(_res) {
	
	compute = new ComputeShader("res/c_shaders/ray_trace.glsl");

	texture = new Texture(NULL, "rtx", 0, res.x, res.y, GL_FLOAT, GL_RGBA32F);
	texture->bindImageTextureMode(GL_WRITE_ONLY, GL_RGBA32F);

	shader = new Shader("res/shaders/f_vert.glsl", "res/shaders/f_frag.glsl");

	renderer = new Renderer2D(initVectorFromArray(FRAME_QUAD, float), 6, GL_TRIANGLES);
	renderer->VertexDataLayout(0, 2, GL_FLOAT, 2 * sizeof(vec2), 0);
	renderer->VertexDataLayout(1, 2, GL_FLOAT, 2 * sizeof(vec2), sizeof(vec2));

	buffer = new Buffer(GL_SHADER_STORAGE_BUFFER);

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
	buffer->del();
	delete buffer;
}

void ray_tracing::setup(uint32_t size) {
	std::vector<Sphere> spheres;
	spheres.reserve(size);

	Random randm = Random(0x5656f4c4);

	for (int i = 0; i < size; i++) {
		Sphere sp = {
			.position = vec3<float>(randm.randr_f(-res.x*0.5f, res.x*.5f), randm.randr_f(-res.y * 0.5f, res.y * .5f), randm.rand_f() * 1000.f),
			.radius = randm.randr_f(100.f, 150.f),
			.material = RayCastMat(
				Color(Math::random_f(i * 200), Math::random_f(i * 300), 0.f, 1.0f)
			)
		};

		spheres.push_back(sp);
	}
	buffer->setBufferData(spheres.data(), spheres.size() * sizeof(spheres[0]));
	compute->use();
	compute->setInt("numSpheres", spheres.size());
}

void ray_tracing::dispatch() {
	buffer->bindBase(1);
	texture->bind(0);
	compute->dispatch(res.x/16, res.y/16);
}

void ray_tracing::render() {
	compute->waitUntilFinish(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	
	texture->texUnit(shader, "tex");
	texture->bind();
	renderer->Draw(shader); 
}


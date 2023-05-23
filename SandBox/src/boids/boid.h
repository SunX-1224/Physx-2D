#pragma once

#include "physx2d.h"

using namespace Physx2D;

struct Agent {
	Entity* self;
	float fov;
	float speed;

	Agent(World* world, vec2 pos, float fov, float speed);
	void align(std::vector<void*>& agents);
	void cohesion(std::vector<void*>& agents);
	void separation(std::vector<void*>& agents);
	void bounds();
};

class Boid :public ScriptObject {
	public:
		uint32_t n_agents;
		std::vector<Agent> agents;
		const float aware_radius = 30.f;

		Boid(uint32_t n);

		virtual void setup() override;

		virtual void update(float delta_time) override;

};

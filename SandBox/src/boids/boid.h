#pragma once

#include "physx2d.h"

using namespace Physx2D;

struct Agent {
	Entity* self;
	float fov;
	float speed;

	Agent(World* world, vec2 pos, float fov, float speed);
};

class Boid :public ScriptObject {
	public:
		uint32_t n_agents;
		std::vector<Agent> agents;
		const float aware_radius = 100.f;

		Boid(uint32_t n);

		virtual void setup() override;

		virtual void update(float delta_time) override;

};

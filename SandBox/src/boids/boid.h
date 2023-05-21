#pragma once

#include "physx2d.h"

using namespace Physx2D;

class Agent {
	public:
		Entity* self;
		float fov, speed;

		Agent(World* world, vec2 pos, float fov, float speed);

		void update(float dt);
};

class Boid :public ScriptObject {
	public:
		uint32_t n_agents;
		std::vector<Agent> agents;

		Boid(uint32_t n);

		virtual void setup() override;

		virtual void update(float delta_time) override;

};

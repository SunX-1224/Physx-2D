#include "boid.h"

Agent::Agent(World* world, vec2 pos, float fov, float speed) {
	this->fov = fov;
	this->speed = speed;

	self = world->CreateEntity();
	Transform* tfr = self->GetComponent<Transform>();
	tfr->Position = pos;
	tfr->Scale = vec2(50.f, 20.f);
	tfr->Rotation = Math::random(0) * Math::PI * 2.f;
	self->AddComponent<SpriteRenderer>(QUAD, Color(1.0f, 0.3f, 0.4f, 1.0f));
	self->AddComponent<RigidBody2D>(KINETIC);
}

void Agent::update(float dt) {
	Transform* tfr = self->GetComponent<Transform>();
	tfr->Rotation += fov * (Math::random(12) - 0.5f) * dt;
	self->GetComponent<RigidBody2D>()->Velocity = vec2(cos(tfr->Rotation), sin(tfr->Rotation)) * speed;
}

Boid::Boid(uint32_t n) : n_agents(n){
	agents.reserve(n);
}

void Boid::setup() {
	for (uint32_t i = 0; i < n_agents; i++) {
		agents.push_back(Agent(self->m_world, vec2((Math::random(i) - 0.5f) * 400.f, (Math::random(i) - 0.5f) * 400.f), 1.f, 50.f));
	}
}

void Boid::update(float delta_time) {
	for (auto& agent : agents)
		agent.update(delta_time);
}

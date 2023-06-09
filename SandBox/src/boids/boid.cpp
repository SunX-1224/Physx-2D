#include "boid.h"

extern template class PHYSX2D_API QuadTree<uint32_t>;

Agent::Agent(World* world, vec2 pos, float fov, float speed) {
	this->fov = fov;
	this->speed = speed;

	self = world->CreateEntity();
	self->AddComponent<SpriteRenderer>(TRIANGLE, Color(Math::random_f(pos.x),Math::random_f(pos.y), Math::random_f(pos.x+pos.y), 1.0f)); //
	
	Transform* tfr = self->GetComponent<Transform>();
	tfr->Position = pos;
	tfr->Scale = vec2(10.f, 5.f);
	tfr->Rotation = Math::random_f(pos.x + pos.y) * Math::PI * 2.f;

	self->AddComponent<RigidBody2D>(KINETIC); //, vec2(speed * cos(tfr->Rotation), speed * sin(tfr->Rotation))
}

void Agent::align(std::vector<void*>& agents) {
	vec2 res;
	for (auto& ag : agents) {
		Agent* agent = (Agent*)ag;
		res += agent->self->GetComponent<RigidBody2D>()->Velocity;
	}
	res *= 1.f / agents.size();
	res = res.normalized() * speed;
	
	RigidBody2D* rgb = self->GetComponent<RigidBody2D>();
	rgb->Acceleration += res - rgb->Velocity;
}

void Agent::cohesion(std::vector<void*>& agents) {
	vec2 res;
	for (auto& ag : agents) {
		Agent* agent = (Agent*)ag;
		res += agent->self->GetComponent<Transform>()->Position;
	}
	res *= 1.f / agents.size();
	res -= self->GetComponent<Transform>()->Position;
	res = res.normalized() * speed;

	RigidBody2D* rgb = self->GetComponent<RigidBody2D>();
	rgb->Acceleration += (res - rgb->Velocity) * 0.96f;
}

void Agent::separation(std::vector<void*>& agents) {
	vec2 res;
	for (auto& ag : agents) {
		Agent* agent = (Agent*)ag;
		vec2 del = self->GetComponent<Transform>()->Position - agent->self->GetComponent<Transform>()->Position;
		del *= 100.f / max(0.001, Math::dot(del, del));
		res += del;
	}
	res *= 1.f / agents.size();
	res = res.normalized() * speed;
	
	RigidBody2D* rgb = self->GetComponent<RigidBody2D>();
	rgb->Acceleration += res - rgb->Velocity;
}

void Agent::bounds() {
	Transform* trf = self->GetComponent<Transform>();

	if (trf->Position.x > 770.f) trf->Position.x = -770.f;
	else if (trf->Position.x < -770.f) trf->Position.x = 770.f;

	if (trf->Position.y > 400.f) trf->Position.y = -400.f;
	else if (trf->Position.y < -400.f) trf->Position.y = 400.f;
}

Boid::Boid(uint32_t n) : n_agents(n){
	agents.reserve(n);
}

void Boid::setup() {
	for (uint32_t i = 0; i < n_agents; i++) {
		agents.push_back(
			Agent(
				self->m_world, 
				vec2((Math::random_f(i*200) - 0.5f) * 1000.f, (Math::random_f(i*300) - 0.5f) * 800.f),
				3.14f,
				250.f)
		);
	}
}

void Boid::update(float delta_time) {
	QuadTree<void*> i_qtree(centerRect(0.f, 0.f, 2000.f, 2000.f));
	for (int i = 0; i < n_agents; i++) 
		i_qtree.insert(agents[i].self->GetComponent<Transform>()->Position, &agents[i]);

	std::vector<void*> others;
	others.reserve(n_agents);
	
	for (uint32_t i = 0; i < n_agents; i++) {
		others.clear();
		i_qtree.query(centerRect(agents[i].self->GetComponent<Transform>()->Position,vec2(aware_radius)),others);

		if (others.size() <= 1) continue;

		agents[i].align(others);
		agents[i].cohesion(others);
		agents[i].separation(others);
		agents[i].bounds();

		RigidBody2D* rgb = agents[i].self->GetComponent<RigidBody2D>();
		agents[i].self->GetComponent<Transform>()->Rotation = atan2(rgb->Velocity.y, rgb->Velocity.x);
	}
}

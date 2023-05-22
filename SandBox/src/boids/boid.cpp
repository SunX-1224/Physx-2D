#include "boid.h"

extern template class PHYSX2D_API QuadTree<uint32_t>;

Agent::Agent(World* world, vec2 pos, float fov, float speed) {
	this->fov = fov;
	this->speed = speed;

	self = world->CreateEntity();
	self->AddComponent<SpriteRenderer>(TRIANGLE, Color(Math::random(pos.x),Math::random(pos.y), Math::random(pos.x+pos.y), 1.0f)); //
	
	Transform* tfr = self->GetComponent<Transform>();
	tfr->Position = pos;
	tfr->Scale = vec2(10.f, 4.f);
	tfr->Rotation = Math::random(pos.x + pos.y) * Math::PI * 2.f;

	self->AddComponent<RigidBody2D>(KINETIC); 
}

Boid::Boid(uint32_t n) : n_agents(n){
	agents.reserve(n);
}

void Boid::setup() {
	for (uint32_t i = 0; i < n_agents; i++) {
		agents.push_back(Agent(self->m_world, vec2((Math::random(i*200) - 0.5f) * 1500.f, (Math::random(i*300) - 0.5f) * 900.f), 1.f, 15.f));
	}
}

void Boid::update(float delta_time) {
	QuadTree<uint32_t> i_qtree(centerRect(0.f, 0.f, 5000.f, 5000.f));
	for (int i = 0; i < n_agents; i++)
		i_qtree.insert(agents[i].self->GetComponent<Transform>()->Position, i);
	
	std::vector<uint32_t> inds;
	inds.reserve(n_agents);
	
	for (uint32_t i = 0; i < n_agents; i++) {
		Transform* trf = agents[i].self->GetComponent<Transform>();

		inds.clear();
		i_qtree.query(centerRect(trf->Position, vec2(aware_radius)), inds);
		if (inds.size() == 0) continue;

		vec2 res;
		float avg = 0;
		vec2 cen;

		for (auto& j : inds) {
			Transform* ntrf = agents[j].self->GetComponent<Transform>();
			avg += ntrf->Rotation;
			cen += ntrf->Position;

			if (i == j) continue;

			vec2 del = trf->Position - ntrf->Position;
			res += del * (1.f / Math::dot(del, del));
		}

		cen *= 1.f / inds.size();
		cen -= trf->Position;
		avg /= inds.size();

		//vec2 drive = vec2(50.f, 100.f) - trf->Position;

		float del = atan2(res.y, res.x) + atan2(cen.y, cen.x) + avg - 3.f * trf->Rotation;
		float rr = (Math::random(TIME*1000) - 0.5f) * agents[i].fov;

		float w8 = 0.5f;
		del = del * w8 + rr * (1.f - w8);

		trf->Rotation += del * delta_time;
		
		agents[i].self->GetComponent<RigidBody2D>()->Velocity =  vec2(cos(trf->Rotation), sin(trf->Rotation)) * agents[i].speed;
	}
}

#include "physx2d.h"

class Gravity : public Physx2D::ScriptObject {
public:

	virtual void setup() override {

		Physx2D::vec2 rp = Physx2D::vec2(Physx2D::Math::randint(-400, 400), Physx2D::Math::randint(-400, 400));
		Physx2D::vec2 sc = Physx2D::vec2(Physx2D::Math::random(1224) * 4.f + 4.f);

		Physx2D::Transform* tfr = self->GetComponent<Physx2D::Transform>();
		tfr->Position = rp;
		tfr->Scale = sc;

		self->AddComponent<Physx2D::RigidBody2D>(Physx2D::KINETIC, rp, Physx2D::vec2(), sc.x, 0.f, 0.8f);
		self->AddComponent<Physx2D::CircleCollider>(Physx2D::vec2(), sc.x * 0.5f);
		self->AddComponent<Physx2D::SpriteRenderer>(Physx2D::CIRCLE, Physx2D::vec4(Physx2D::Math::random(1224), Physx2D::Math::random(1223), 0.5f, 1.f));
	}

	virtual void update() override {

		if (self->HasComponent<Physx2D::RigidBody2D>()) {
			Physx2D::RigidBody2D* rgb = self->GetComponent<Physx2D::RigidBody2D>();
			Physx2D::Transform* trf = self->GetComponent<Physx2D::Transform>();
			rgb->Acceleration = Physx2D::vec2(0.f, -100.f);
		}
		if (self->HasComponent<Physx2D::SpriteRenderer>()) {
			Physx2D::SpriteRenderer* rdr1 = self->GetComponent<Physx2D::SpriteRenderer>();
			rdr1->color += Physx2D::Color(-0.1f, 0.f, 0.2f, 0.f);
		}
	}

	virtual void OnCollisionDetected(Physx2D::CollisionData& data, Physx2D::Entity* other) {
		Physx2D::SpriteRenderer* rdr1 = self->GetComponent<Physx2D::SpriteRenderer>();
		Physx2D::SpriteRenderer* rdr2 = other->GetComponent<Physx2D::SpriteRenderer>();

		rdr1->color += Physx2D::Color(0.05f, 0.f, -0.1f, 0.f);
		rdr2->color += Physx2D::Color(0.05f, 0.f, -0.1f, 0.f);
	}
};


class SandBox :public Physx2D::Application {

public:
	Physx2D::Window* window;
	Physx2D::World* world;

	SandBox() {
		window = new Physx2D::Window();
		window->Init();

		world = new Physx2D::World(window);
		//bounds
		{
			Physx2D::Entity* entity = world->CreateEntity();
			Physx2D::Transform* tfr = entity->GetComponent<Physx2D::Transform>();
			tfr->Scale = window->GetResolution();
			entity->AddComponent<Physx2D::AABB>(Physx2D::vec2(), tfr->Scale);
			entity->AddComponent<Physx2D::RigidBody2D>();
			entity->AddComponent<Physx2D::SpriteRenderer>(Physx2D::QUAD, Physx2D::Color(0.1f, 0.2f, 0.2f, 0.3f));
		}
		for (int i = 0; i < 500; i++) {
			Physx2D::Entity* entity = world->CreateEntity(std::string("entity"));
			Gravity* grv = new Gravity();
			entity->AddComponent<Physx2D::ScriptComponent>(grv);
		}
		
		world->Initialize();
	}
	~SandBox() {
		delete world;
		delete window;
	}

	virtual void Run() override {
		Physx2D::Time clock;
		clock.initTimer();

		while (!window->ShouldClose()) {
			window->UpdateEvents();

			world->Update(clock.get_delta_time());

			window->FillScreen(Physx2D::Color(0.05f, 0.05f, 0.05f, 1.f));
			world->Render();
			
			window->Update();
			clock.update();
			window->SetTitle((std::to_string(clock.get_fps())).c_str());
		}
		window->Destroy();
	}
};


Physx2D::Application* Physx2D::CreateApplication() {
	return new SandBox();
}

#include "pch.h"
#include "entity.h"

Physx2D::Entity::Entity(EntityID id, World* world_) : m_ID(id), m_world(world_){
	
}

Physx2D::Entity::~Entity() {
	
		RemoveComponent<Transform>();
		RemoveComponent<Tag>();
		RemoveComponent<RigidBody2D>();
		RemoveComponent<SpriteRenderer>();
		RemoveComponent<ScriptComponent>();

		Collider* cldr = GetComponent<Collider>();

		if (cldr->typeIndex == std::type_index(typeid(CircleCollider)))
			delete ((CircleCollider*)cldr);
		else if (cldr->typeIndex == std::type_index(typeid(BoxCollider2D)))
			delete ((BoxCollider2D*)cldr);
		else if (cldr->typeIndex == std::type_index(typeid(BoundingCircle)))
			delete ((BoundingCircle*)cldr);
		else
			delete ((AABB*)cldr);

		LOG_INFO("deleted%c", '\n')
}

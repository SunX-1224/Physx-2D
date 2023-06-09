#pragma once

#include "../scene/components.h"

namespace Physx2D{
		
	class PhysicsHandler {
		
	public:
		static CollisionData checkCollision(Collider* c1, Transform* t1, BodyType s1, Collider* c2, Transform* t2, BodyType s2);

		static void collisionPhysics(CollisionData data, RigidBody2D* dynamicBody, RigidBody2D* body2);

		static void updateRigidBody(RigidBody2D* body, Transform* transform, float delta_time);

	private:

		static CollisionData _check(CircleCollider* c1, Transform* t1, CircleCollider* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, BoundingCircle* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, AABB* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, BoxCollider2D* c2, Transform* t2);

		static CollisionData _check(BoxCollider2D* c1, Transform* t1, BoxCollider2D* c2, Transform* t2);

		//TODO : Box bounds
		static CollisionData _check(BoxCollider2D* c1, Transform* t1, AABB* c2, Transform* t2);
		static CollisionData _check(BoxCollider2D* c1, Transform* t1, BoundingCircle* c2, Transform* t2);
	};
}

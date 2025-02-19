#pragma once

#include "Vector3.h"
#include "PhysicsObject.h"

//Include colliders
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "SimplePlaneCollider.h"

struct CollisionData {
	float penetrationDepth{};
	Vector3 normal; //collision normal
	PhysicsObject* pObj1{};
	PhysicsObject* pObj2{};
};
//global collision detection functions
bool OverlapSphere2Sphere(const Vector3& pos1, float r1, const Vector3& pos2, float r2);
bool OverlapSphere2Sphere(PhysicsObject& obj1, float r1, PhysicsObject& obj2, float r2, CollisionData& cd);
//bool OverlapAABB2AABB(const Vector3& min1, const Vector3& max1,
//					  const Vector3& min2, const Vector3& max2);
//bool OverlapAABB2AABB(PhysicsObject& box1, float width1, float height1,
//					  PhysicsObject& box2, float width2, float height2,
//					  CollisionData& cd);
bool OverlapSphere2Plane(PhysicsObject& Sphere, CircleCollider& SphereHitbox,SimplePlaneCollider& PlaneHitbox);
bool OverlapSphere2AABB(Vector3 SpherePos, float radius, Vector3 boxMin, Vector3 boxMax);
bool OverlapSimpleCube2Plane(PhysicsObject& Cube, BoxCollider& Hitbox, PhysicsObject& Plane,SimplePlaneCollider& PlaneHitbox, CollisionData& cd);
bool OverlapCube2Cube(PhysicsObject& Cube, BoxCollider& Hitbox, PhysicsObject& Cube2, BoxCollider& Hitbox2, CollisionData& cd);
bool OverlapSphere2Cube(PhysicsObject& Sphere, CircleCollider& SphereHitbox, PhysicsObject& Cube, BoxCollider& CubeHitbox, CollisionData& cd);
//collision resolution function
//void ResolveSphere2StaticPlane(PhysicsObject& ball, float radius, const Vector3& min, const Vector3& max);
//void ResolveSphere2StaticSphere(PhysicsObject& ball1, float radius1, PhysicsObject& ball2, float radius2);
void ResolveCollision(CollisionData& cd);

//void ResolveSphere2AABB(PhysicsObject& Sphere, float radius, Vector3 boxMin, Vector3 boxMax);
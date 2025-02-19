#include "CollisionDetection.h"
#include <iostream>

bool OverlapSphere2Sphere(const Vector3& pos1, float r1, const Vector3& pos2, float r2)
{
	Vector3 distance = pos1 - pos2;
	float sumRadius = (r1 + r2) * (r1 + r2);
	if (distance.LengthSquared() <= sumRadius) {
		return true;
	}
	return false;
}

bool OverlapSphere2Sphere(PhysicsObject& obj1, float r1, PhysicsObject& obj2, float r2, CollisionData& cd)
{
	Vector3 displacementVector = obj1.getPosition() - obj2.getPosition();
	float squaredLength = (obj1.getPosition() - obj2.getPosition()).LengthSquared();
	if (squaredLength <= (r1 + r2) * (r1 + r2)) { //check for overlap
		//calculate collision data
		//assign collsion to pointers
		cd.pObj1 = &obj1;
		cd.pObj2 = &obj2;
		float length = displacementVector.Length();
		cd.penetrationDepth = (r1 + r2) - length; //calculate the amount of overlap
		cd.normal = displacementVector.Normalize(); //calculate the normal
		return true;
	}
	return false;
}

void ResolveCollision(CollisionData& cd)
{
	PhysicsObject& obj1 = *cd.pObj1; //Reference to the collision object
	PhysicsObject& obj2 = *cd.pObj2; //Reference to the collision object
	float totalInvMass = 1.f / (obj1.getMass() + obj2.getMass());
	if ((obj1.getMass() > 0) && (obj2.getMass() == 0)) {
		Vector3 deltaVelocity = (obj1.getVel().Dot(cd.normal) - obj2.getVel().Dot(cd.normal)) * cd.normal;
		obj1.setVel(obj1.getVel() - (1.f + obj1.getBounciness()) * deltaVelocity);
		obj1.translateObject(totalInvMass * cd.penetrationDepth * cd.normal);
	}
	else if ((obj1.getMass() == 0) && (obj2.getMass() > 0)) {
		Vector3 deltaVelocity = (obj2.getVel().Dot(cd.normal) - obj1.getVel().Dot(cd.normal)) * cd.normal;
		obj2.setVel(obj2.getVel() - (1.f + obj2.getBounciness()) * deltaVelocity);
		obj2.translateObject(totalInvMass * cd.penetrationDepth * cd.normal);
	}
	else
	{
		obj1.translateObject(obj2.getMass() * totalInvMass * cd.penetrationDepth * cd.normal); //cd.normal is displacementVec.normal
		obj2.translateObject(obj1.getMass() * totalInvMass * cd.penetrationDepth * -cd.normal); //displacementVec is destination - source
		//resolve velocity
		Vector3 deltaVelocity = (obj1.getVel().Dot(cd.normal) - obj2.getVel().Dot(cd.normal)) * cd.normal;
		obj1.setVel(obj1.getVel() - (1.f + obj1.getBounciness()) * obj2.getMass() * totalInvMass * deltaVelocity);
		obj2.setVel(obj2.getVel() + (1.f + obj2.getBounciness()) * obj1.getMass() * totalInvMass * deltaVelocity);
	}
}

bool OverlapSphere2Plane(PhysicsObject& Sphere, CircleCollider& SphereHitbox, SimplePlaneCollider& PlaneHitbox)
{
	Vector3 nearestPoint;
	if (Sphere.getPosition().x < PlaneHitbox.getMin().x) {
		nearestPoint.x = PlaneHitbox.getMin().x;
	}
	else if (Sphere.getPosition().x > PlaneHitbox.getMax().x) {
		nearestPoint.x = PlaneHitbox.getMax().x;
	}
	else {
		nearestPoint.x = Sphere.getPosition().x;
	}
	if (Sphere.getPosition().z < PlaneHitbox.getMin().z) {
		nearestPoint.z = PlaneHitbox.getMin().z;
	}
	else if (Sphere.getPosition().z > PlaneHitbox.getMax().z) {
		nearestPoint.z = PlaneHitbox.getMax().z;
	}
	else {
		nearestPoint.z = Sphere.getPosition().z;
	}
	nearestPoint.y = PlaneHitbox.getMax().y; //does not matter since all vertice y values should be the same as this is simple plane hitbox
	if ((Sphere.getPosition() - nearestPoint).Length() > SphereHitbox.getRadius())
	{
		return false; //not colliding
	}
	float penetratedDist = SphereHitbox.getRadius() - (nearestPoint - Sphere.getPosition()).Length();
	Sphere.translateObject(penetratedDist * (Sphere.getPosition() - nearestPoint).Normalized());
	//Resolve Velocity
	Vector3 changeInVel = Sphere.getVel().Dot((Sphere.getPosition() - nearestPoint).Normalize()) * (Sphere.getPosition() - nearestPoint).Normalize();
	Sphere.setVel(Sphere.getVel() - (1 + Sphere.getBounciness()) * changeInVel);
	return true;
}

bool OverlapSphere2AABB(Vector3 SpherePos, float radius, Vector3 boxMin, Vector3 boxMax)
{
	return false;
}

bool OverlapSimpleCube2Plane(PhysicsObject& Cube, BoxCollider& Hitbox, PhysicsObject& Plane, SimplePlaneCollider& PlaneHitbox, CollisionData& cd)
{
	if (Hitbox.getMin().x > PlaneHitbox.getMax().x || Hitbox.getMax().x < PlaneHitbox.getMin().x ||
		Hitbox.getMin().y > PlaneHitbox.getMax().y || Hitbox.getMax().y < PlaneHitbox.getMin().y ||
		Hitbox.getMin().z > PlaneHitbox.getMax().z || Hitbox.getMax().z < PlaneHitbox.getMin().z)
		return false; //if not colliding
	//Compute penetration distance for all sides
		// pd for left
	float left = Hitbox.getMax().x - PlaneHitbox.getMin().x;
	// pd for right
	float right = PlaneHitbox.getMax().x - Hitbox.getMin().x;
	// pd for top
	float top = PlaneHitbox.getMax().y - Hitbox.getMin().y;
	// pd for bottom
	float bottom = Hitbox.getMax().y - PlaneHitbox.getMin().y;
	// pd for front
	float front = PlaneHitbox.getMax().z - Hitbox.getMin().z;
	// pd for back
	float back = Hitbox.getMax().z - PlaneHitbox.getMin().z;
	//Find minimum penetration distance
	float smallestPD = left;
	if (right < smallestPD)
		smallestPD = right;
	if (top < smallestPD)
		smallestPD = top;
	if (bottom < smallestPD)
		smallestPD = bottom;
	if (front < smallestPD)
		smallestPD = front;
	if (back < smallestPD)
		smallestPD = back;
	cd.penetrationDepth = smallestPD;
	cd.pObj1 = &Cube;
	cd.pObj2 = &Plane;
	cd.normal = (Cube.getPosition() - Plane.getPosition()).Normalize();
	return true;
}

bool OverlapCube2Cube(PhysicsObject& Cube, BoxCollider& Hitbox, PhysicsObject& Cube2, BoxCollider& Hitbox2, CollisionData& cd)
{
	if (Hitbox.getMin().x > Hitbox2.getMax().x || Hitbox.getMax().x < Hitbox2.getMin().x ||
		Hitbox.getMin().y > Hitbox2.getMax().y || Hitbox.getMax().y < Hitbox2.getMin().y ||
		Hitbox.getMin().z > Hitbox2.getMax().z || Hitbox.getMax().z < Hitbox2.getMin().z)
		return false; //if not colliding
	//Compute penetration distance for all sides
		// pd for left
	float left = Hitbox.getMax().z - Hitbox2.getMin().z;
	// pd for right
	float right = Hitbox2.getMax().z - Hitbox.getMin().z;
	// pd for top
	float top = Hitbox2.getMax().y - Hitbox.getMin().y;
	// pd for bottom
	float bottom = Hitbox.getMax().y - Hitbox2.getMin().y;
	// pd for front
	float front = Hitbox2.getMax().x - Hitbox.getMin().x;
	// pd for back
	float back = Hitbox.getMax().x - Hitbox2.getMin().x;
	//Find minimum penetration distance
	float smallestPD = left;
	if (right < smallestPD)
		smallestPD = right;
	if (top < smallestPD)
		smallestPD = top;
	if (bottom < smallestPD)
		smallestPD = bottom;
	if (front < smallestPD)
		smallestPD = front;
	if (back < smallestPD)
		smallestPD = back;
	//resolve collision
	cd.penetrationDepth = smallestPD;
	cd.pObj1 = &Cube;
	cd.pObj2 = &Cube2;
	cd.normal = (Cube.getPosition() - Cube2.getPosition()).Normalize();
	return true;
}

bool OverlapSphere2Cube(PhysicsObject& Sphere, CircleCollider& SphereHitbox, PhysicsObject& Cube, BoxCollider& CubeHitbox, CollisionData& cd)
{
	Vector3 nearestPoint;
	if (Sphere.getPosition().x < CubeHitbox.getMin().x) {
		nearestPoint.x = CubeHitbox.getMin().x;
	}
	else if (Sphere.getPosition().x > CubeHitbox.getMax().x) {
		nearestPoint.x = CubeHitbox.getMax().x;
	}
	else {
		nearestPoint.x = Sphere.getPosition().x;
	}
	if (Sphere.getPosition().y < CubeHitbox.getMin().y) {
		nearestPoint.y = CubeHitbox.getMin().y;
	}
	else if (Sphere.getPosition().z > CubeHitbox.getMax().y) {
		nearestPoint.y = CubeHitbox.getMax().y;
	}
	else {
		nearestPoint.y = Sphere.getPosition().y;
	}
	if (Sphere.getPosition().z < CubeHitbox.getMin().z) {
		nearestPoint.z = CubeHitbox.getMin().z;
	}
	else if (Sphere.getPosition().z > CubeHitbox.getMax().z) {
		nearestPoint.z = CubeHitbox.getMax().z;
	}
	else {
		nearestPoint.z = Sphere.getPosition().z;
	}
	if ((Sphere.getPosition() - nearestPoint).Length() > SphereHitbox.getRadius())
	{
		return false; //not colliding
	}
	cd.penetrationDepth = SphereHitbox.getRadius() - (nearestPoint - Sphere.getPosition()).Length();
	cd.pObj1 = &Sphere;
	cd.pObj2 = &Cube;
	cd.normal = (Sphere.getPosition() - Cube.getPosition()).Normalize();
	return true;
}

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
		obj1.translatePosition(totalInvMass * cd.penetrationDepth * cd.normal);
	}
	else if ((obj1.getMass() == 0) && (obj2.getMass() > 0)) {
		Vector3 deltaVelocity = (obj2.getVel().Dot(cd.normal) - obj1.getVel().Dot(cd.normal)) * cd.normal;
		obj2.setVel(obj2.getVel() - (1.f + obj2.getBounciness()) * deltaVelocity);
		obj2.translatePosition(totalInvMass * cd.penetrationDepth * cd.normal);
	}
	else
	{
		obj1.translatePosition(obj2.getMass() * totalInvMass * cd.penetrationDepth * cd.normal); //cd.normal is displacementVec.normal
		obj2.translatePosition(obj1.getMass() * totalInvMass * cd.penetrationDepth * -cd.normal); //displacementVec is destination - source
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
	Sphere.translatePosition(penetratedDist * (Sphere.getPosition() - nearestPoint).Normalized());
	//Resolve Velocity
	Vector3 changeInVel = Sphere.getVel().Dot((Sphere.getPosition() - nearestPoint).Normalize()) * (Sphere.getPosition() - nearestPoint).Normalize();
	Sphere.setVel(Sphere.getVel() - (1 + Sphere.getBounciness()) * changeInVel);
	return true;
}

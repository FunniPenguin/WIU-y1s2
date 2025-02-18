#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "GameObject.h"

//Vector class is from FORMOP, only extra thing added was conversion from Vector3 to glm::vec3 and contructor with glm::vec3
#include "Vector3.h"

//Done by DylanYap, meant to replicate unity physics objects
class PhysicsObject : public GameObject
{
private:
	//Note that physics object attributes should generally be zero except for gravity
	Vector3 vel;
	Vector3 accel;
	float mass;
	float gravity;

	//for angular movement
	Vector3 angularVel; //degrees per second
	float bounciness;

public:
	Vector3 getVel();
	void setVel(Vector3 Vel);
	void setVel(float x, float y, float z);
	Vector3 getAccel();
	void setAccel(Vector3 Accel);
	void setAccel(float x, float y, float z);
	float getGravity();
	void setGravity(float Gravity);
	float getMass();
	void setMass(float Mass);
	float getBounciness();
	void setBounciness(int Bounciness);

	void AddForce(const Vector3& force); //add a pushing force through the center of mass
	void UpdatePhysics(float dt);
	void AddImpulse(const Vector3& impulse);

	PhysicsObject();
	PhysicsObject(int Gravity);
	PhysicsObject(Vector3 Position);
	PhysicsObject(Vector3 Position, int Gravity);
	~PhysicsObject() {};
private:
	Vector3 m_totalForces;
};

#endif
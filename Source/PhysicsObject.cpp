#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : GameObject()
{
	vel = Vector3{ 0, 0, 0 };
	accel = Vector3{ 0, 0, 0 };
	mass = 1;
	angularVel = Vector3{ 0, 0, 0 };
	gravity = 0;
	bounciness = 1;
}

PhysicsObject::PhysicsObject(int Gravity) : GameObject()
{
	vel = Vector3{ 0, 0, 0 };
	accel = Vector3{ 0, 0, 0 };
	mass = 1;
	angularVel = Vector3{ 0, 0, 0 };
	gravity = Gravity;
	bounciness = 1;
}

PhysicsObject::PhysicsObject(Vector3 Position) : GameObject(Position)
{
	vel = Vector3{ 0, 0, 0 };
	accel = Vector3{ 0, 0, 0 };
	mass = 1;
	angularVel = Vector3{ 0, 0, 0 };
	gravity = 0;
	bounciness = 1;
}

PhysicsObject::PhysicsObject(Vector3 Position, int Gravity) : GameObject(Position)
{
	vel = Vector3{ 0, 0, 0 };
	accel = Vector3{ 0, 0, 0 };
	mass = 1;
	angularVel = Vector3{ 0, 0, 0 };
	gravity = Gravity;
	bounciness = 1;
}

Vector3 PhysicsObject::getVel()
{
	return vel;
}

void PhysicsObject::setVel(Vector3 Vel)
{
	vel = Vel;
}

void PhysicsObject::setVEl(float x, float y, float z)
{
	vel = Vector3{ x, y, z };
}

Vector3 PhysicsObject::getAccel()
{
	return accel;
}

void PhysicsObject::setAccel(Vector3 Accel)
{
	accel = Accel;
}

void PhysicsObject::setAccel(float x, float y, float z)
{
	accel = Vector3{ x,y,z };
}

float PhysicsObject::getGravity()
{
	return gravity;
}

void PhysicsObject::setGravity(float Gravity)
{
	gravity = Gravity;
}

float PhysicsObject::getMass()
{
	return mass;
}

void PhysicsObject::setMass(float Mass)
{
	mass = Mass;
}

float PhysicsObject::getBounciness()
{
	return bounciness;
}

void PhysicsObject::setBounciness(int Bounciness)
{
	bounciness = Bounciness;
}

void PhysicsObject::AddForce(const Vector3& force)
{
	m_totalForces += force;
}

void PhysicsObject::UpdatePhysics(float dt)
{
	Vector3 Gravity{ 0, -gravity, 0 };
	Vector3 initialVelocity = vel;
	vel += Gravity * dt;
	translatePosition((vel + initialVelocity) * 0.5f * dt);
	Vector3 finalAccel = accel;
	//if mass is 0, treat object as static/immovable
	if (mass > 0)
	{
		//F = MA
		float invMass = 1.f / mass;
		finalAccel = accel + m_totalForces * invMass;
	}

	//euler integration
	vel += finalAccel * dt;
	translatePosition(vel * dt);

	//clear forces
	m_totalForces.SetZero();

	//do angular movement
	addRotation(angularVel * dt);
}

void PhysicsObject::AddImpulse(const Vector3& impulse)
{
	vel += impulse * (1 / mass);
}

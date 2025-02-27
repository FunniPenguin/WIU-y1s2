#include "Fence.h"

void Fence::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Fence::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Fence::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setPosition(Position);
}

bool Fence::getIsVert() const
{
	return IsVert;
}

int Fence::getFenceNo() const
{
	return fenceNo;
}

BoxCollider& Fence::getHitbox()
{
	return hitbox;
}



Fence::Fence(Vector3 Position, float HalfLength, float HalfHeight, float HalfBreath, bool isVert, int FenceNo) : PhysicsObject(Position, 0), hitbox(Position, HalfLength, HalfHeight, HalfBreath)
{
	setMass(0);
	IsVert = isVert;
	fenceNo = FenceNo;
}

Fence::~Fence()
{
}

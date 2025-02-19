#include "Ground.h"

void Ground::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Ground::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Ground::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setPosition(Position);
}

SimplePlaneCollider& Ground::getHitbox()
{
	return hitbox;
}



Ground::Ground(Vector3 Position, Vector3 Translation1, Vector3 Translation2) : PhysicsObject(Position, 0), hitbox(Position, Translation1, Translation2)
{
	setMass(0);
}

Ground::~Ground()
{
}

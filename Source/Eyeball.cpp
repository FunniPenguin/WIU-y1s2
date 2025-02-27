#include "Eyeball.h"

void Eyeball::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Eyeball::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Eyeball::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

CircleCollider& Eyeball::getHitbox()
{
	return hitbox;
}



Eyeball::Eyeball(Vector3 Position, float Radius,  float Gravity) : PhysicsObject(Position, Gravity), hitbox(Position, Radius)
{
	setBounciness(0.5f);
}

Eyeball::~Eyeball()
{
}

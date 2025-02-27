#include "Dart.h"

void Dart::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Dart::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Dart::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

CircleCollider& Dart::getHitbox()
{
	return hitbox;
}



Dart::Dart(Vector3 Position, float Radius,  float Gravity) : PhysicsObject(Position, Gravity), hitbox(Position, Radius)
{
	setBounciness(0.5f);
}

Dart::~Dart()
{
}

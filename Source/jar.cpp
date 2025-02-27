#include "Jar.h"

void Jar::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Jar::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Jar::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

CircleCollider& Jar::getHitbox()
{
	return hitbox;
}



Jar::Jar(Vector3 Position) : GameObject(Position), hitbox(Position, 2.f)
{
}

Jar::~Jar()
{
}

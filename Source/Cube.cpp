#include "Cube.h"

void Cube::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Cube::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Cube::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setPosition(Position);
}

BoxCollider& Cube::getHitbox()
{
	return hitbox;
}



Cube::Cube(Vector3 Position, float Gravity, float HalfLength, float HalfBreath, float HalfHeight) : PhysicsObject(Position, Gravity), hitbox(Position, HalfLength, HalfBreath, HalfHeight)
{
}

Cube::~Cube()
{
}

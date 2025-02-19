#include "Ball.h"

void Ball::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Ball::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Ball::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

CircleCollider& Ball::getHitbox()
{
	return hitbox;
}



Ball::Ball(Vector3 Position, float Radius,  float Gravity) : PhysicsObject(Position, Gravity), hitbox(Position, Radius)
{
}

Ball::~Ball()
{
}

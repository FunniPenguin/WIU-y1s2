#include "Ball.h"

void Ball::setBallPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

void Ball::setBallPosition(AXIS axis, int value)
{
	setPosition(axis, value);
	if (axis == X_AXIS)
		hitbox.setOrigin(Vector3(getPosition().x + value, getPosition().y, getPosition().z));
	else if (axis == Y_AXIS)
		hitbox.setOrigin(Vector3(getPosition().x, getPosition().y + value, getPosition().z));
	else if (axis == Z_AXIS)
		hitbox.setOrigin(Vector3(getPosition().x, getPosition().y, getPosition().z + value));
}

void Ball::translateBall(Vector3 translation)
{
	translateBall(translation);
	hitbox.translate(translation);
}

void Ball::translateBall(glm::vec3 translation)
{
	translateBall(translation);
	hitbox.translate(translation);
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

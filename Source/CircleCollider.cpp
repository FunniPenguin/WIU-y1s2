#include "CircleCollider.h"

void CircleCollider::setOrigin(Vector3 Origin)
{
	origin = Origin;
}

void CircleCollider::setOrigin(glm::vec3 Origin)
{
	origin = Vector3(Origin);
}

void CircleCollider::translate(Vector3 translation)
{
	origin += translation;
}

void CircleCollider::translate(glm::vec3 translation)
{
	origin += Vector3(translation);
}

float CircleCollider::getRadius()
{
	return radius;
}

void CircleCollider::setRadius(int Radius)
{
	radius = Radius;
}

CircleCollider::CircleCollider(Vector3 Origin, int Radius)
{
	origin = Origin;
	radius = Radius;
}

CircleCollider::~CircleCollider()
{
}

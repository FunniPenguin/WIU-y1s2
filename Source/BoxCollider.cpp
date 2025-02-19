#include "BoxCollider.h"

void BoxCollider::setPosition(Vector3 Origin)
{
	max = Origin + halfDimensions;
	min = Origin - halfDimensions;
}

void BoxCollider::setPosition(glm::vec3 Origin)
{
	max = Vector3(Origin) + halfDimensions;
	min = Vector3(Origin) - halfDimensions;
}

void BoxCollider::translate(Vector3 translation)
{
	max += translation;
	min += translation;
}

void BoxCollider::translate(glm::vec3 translation)
{
	max += translation;
	min += translation;
}

Vector3& BoxCollider::getMin()
{
	return min;
}

Vector3& BoxCollider::getMax()
{
	return max;
}

Vector3& BoxCollider::getHalfDimensions()
{
	return halfDimensions;
}



BoxCollider::BoxCollider(Vector3 Origin, float HalfLength, float HalfHeight,float HalfBreath)
{
	halfDimensions.x = abs(HalfLength);
	halfDimensions.y = abs(HalfHeight);
	halfDimensions.z = abs(HalfBreath);
	max = Origin + halfDimensions;
	min = Origin - halfDimensions;
}

BoxCollider::BoxCollider(Vector3 Origin, Vector3 HalfDimensions)
{
	halfDimensions = Vector3(abs(HalfDimensions.x), abs(HalfDimensions.y), abs(HalfDimensions.z));
	max = Origin + halfDimensions;
	min = Origin - halfDimensions;
}

BoxCollider::~BoxCollider()
{
}

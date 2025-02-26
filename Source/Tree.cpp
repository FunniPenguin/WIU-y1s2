#include "Tree.h"

void Tree::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Tree::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Tree::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setOrigin(Position);
}

CircleCollider& Tree::getHitbox()
{
	return hitbox;
}



Tree::Tree(Vector3 Position, float Radius,  float Gravity) : PhysicsObject(Position, Gravity), hitbox(Position, Radius)
{
}

Tree::~Tree()
{
}

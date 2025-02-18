#ifndef BALL_H
#define BALL_H

#include "Vector3.h"
#include "PhysicsObject.h"
#include "CircleCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class Ball : public PhysicsObject
{
private:
	CircleCollider hitbox;
public:
	//Note: Overload a game object's set and translate functions if the object has a hitbox so that the hibox gets moved
	void setBallPosition(Vector3 Position);
	void setBallPosition(AXIS axis, int value);
	void translateBall(Vector3 translation);
	void translateBall(glm::vec3 translation);

	CircleCollider& getHitbox();

	Ball(Vector3 Position, float Radius, float Gravity);
	~Ball();
};

#endif
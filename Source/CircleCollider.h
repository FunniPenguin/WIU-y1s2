#ifndef CIRCLE_COLLIRDER_H
#define CIRCLE_COLLIRDER_H

#include "Vector3.h"
#include "BaseCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class CircleCollider : public BaseCollider
{
private:
	float radius;
	Vector3 origin;
public:
	void setOrigin(Vector3 Origin);
	void setOrigin(glm::vec3 Origin);
	//Not explicitly saying translate ball collider as the translation would be assigned to hitbox due to it being an attribute
	void translate(Vector3 translation);
	void translate(glm::vec3 translation);

	float getRadius();
	void setRadius(int Radius);

	CircleCollider(Vector3 Origin, int Radius);
	~CircleCollider();
};

#endif
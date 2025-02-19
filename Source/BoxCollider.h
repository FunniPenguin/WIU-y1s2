#ifndef BOX_COLLIRDER_H
#define BOX_COLLIRDER_H

#include "Vector3.h"
#include "BaseCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class BoxCollider : public BaseCollider
{
private:
	Vector3 min;
	Vector3 max;
	Vector3 halfDimensions;
public:
	void setPosition(Vector3 Origin);
	void setPosition(glm::vec3 Origin);
	void translate(Vector3 translation);
	void translate(glm::vec3 translation);
	Vector3& getMin();
	Vector3& getMax();
	Vector3& getHalfDimensions();

	//Note: Only need the min and max to calculate the box
	BoxCollider( Vector3 Origin, float HalfLength, float HalfHeight, float HalfBreath);
	BoxCollider(Vector3 Origin, Vector3 HalfDimensions);
	~BoxCollider();
};

#endif
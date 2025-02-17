#ifndef BASE_COLLIRDER_H
#define BASE_COLLIRDER_H

#include "Vector3.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class BaseCollider
{
private:
public:
	virtual void translate(Vector3 translation) = 0;
	virtual void translate(glm::vec3 translation) = 0;
	BaseCollider() {};
	~BaseCollider() {};
};

#endif
#ifndef GROUND_H
#define GROUND_H

#include "Vector3.h"
#include "PhysicsObject.h"
#include "SimplePlaneCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class Ground : public PhysicsObject
{
private:
	SimplePlaneCollider hitbox;
public:
	//Note: Overload a game object's set and translate functions if the object has a hitbox so that the hibox gets moved
	void translateObject(Vector3 translation);
	void translateObject(glm::vec3 translation);
	void setObjectPosition(Vector3 Position);
	SimplePlaneCollider& getHitbox();

	Ground(Vector3 Position, Vector3 Translation1, Vector3 Translation2);
	~Ground();
};

#endif
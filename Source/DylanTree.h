#ifndef DYLANTREE_H
#define DYLANTREE_H

#include "Vector3.h"
#include "GameObject.h"
#include "CircleCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class DylanTree : public GameObject
{
private:

public:
	//Note: Overload a game object's set and translate functions if the object has a hitbox so that the hibox gets moved

	DylanTree(Vector3 Position);
	~DylanTree();
};

#endif
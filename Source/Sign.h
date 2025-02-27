#ifndef SIGN_H
#define SIGN_H

#include <vector>
#include <fstream>

#include "Vector3.h"
#include "InteractableObject.h"
#include "CircleCollider.h"
#include "Player.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class Sign : public InteractableObject
{
private:
	float radius; //Not using a collider as I expect the player to be able to walk over the Sign
	//just need to check if the player can pick up the newspapaer
public:
	//Note: For this object, no need to overload the translate and set obj functions as there is no hitbox
	void interact(Player& Player);
	float getRadius();

	Sign(Vector3 Position, std::string Name);
	~Sign();
};

#endif
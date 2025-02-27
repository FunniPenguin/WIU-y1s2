#ifndef SCISSOR_H
#define SCISSOR_H

#include <vector>
#include <fstream>

#include "Vector3.h"
#include "InteractableObject.h"
#include "Player.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class Scissor : public InteractableObject
{
private:
	float radius; //Not using a collider as I expect the player to be able to walk over the Scissor
	//just need to check if the player can pick up the newspapaer
public:
	//Note: For this object, no need to overload the translate and set obj functions as there is no hitbox
	void interact(Player& Player);
	float getRadius();

	Scissor(Vector3 Position);
	~Scissor();
};

#endif
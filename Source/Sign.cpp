#include "Sign.h"

//Standard file reading libraries
#include <iostream>
#include <sstream>

#include "KeyboardController.h"
#include "MouseController.h"
#include "Inventory.h"

//Include GLFW
#include <GLFW/glfw3.h>

void Sign::interact(Player& Player)
{
	setCurrDialogue(0);
	return;
}

float Sign::getRadius()
{
	return radius;
}

Sign::Sign(Vector3 Position, std::string Name) : InteractableObject(Name, Position)
{
	radius = 3.f;
}

Sign::~Sign()
{
}

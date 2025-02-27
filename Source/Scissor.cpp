#include "Scissor.h"

//Standard file reading libraries
#include <iostream>
#include <sstream>

#include "KeyboardController.h"
#include "MouseController.h"
#include "Inventory.h"

//Include GLFW
#include <GLFW/glfw3.h>

void Scissor::interact(Player& Player)
{
	setCurrDialogue(0);
	Inventory::GetInstance().addItem("scissor");
	return;
}

float Scissor::getRadius()
{
	return radius;
}

Scissor::Scissor(Vector3 Position) : InteractableObject("scissor", Position)
{
	radius = 3.f;
}

Scissor::~Scissor()
{
}

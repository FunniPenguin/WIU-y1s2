#include "Newspaper.h"

//Standard file reading libraries
#include <iostream>
#include <sstream>

#include "KeyboardController.h"
#include "MouseController.h"
#include "Inventory.h"

//Include GLFW
#include <GLFW/glfw3.h>

void Newspaper::interact(Player& Player)
{
	setCurrDialogue(0);
	Inventory::GetInstance().addItem("newspaper1");
	return;
}

float Newspaper::getRadius()
{
	return radius;
}

Newspaper::Newspaper(Vector3 Position, std::string Name) : InteractableObject(Name, Position)
{
	radius = 3.f;
}

Newspaper::~Newspaper()
{
}

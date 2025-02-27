#include "TornRecordPage3.h"

//Standard file reading libraries
#include <iostream>
#include <sstream>

#include "KeyboardController.h"
#include "MouseController.h"
#include "Inventory.h"

//Include GLFW
#include <GLFW/glfw3.h>

void TornRecordPage3::interact(Player& Player)
{
	setCurrDialogue(0);
	Inventory::GetInstance().addItem("tornrecordpage3");
	return;
}

float TornRecordPage3::getRadius()
{
	return radius;
}

TornRecordPage3::TornRecordPage3(Vector3 Position, std::string Name) : InteractableObject(Name, Position)
{
	radius = 3.f;
}

TornRecordPage3::~TornRecordPage3()
{
}

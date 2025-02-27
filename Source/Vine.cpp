#include "Vine.h"

//Standard file reading libraries
#include <iostream>
#include <sstream>

#include "KeyboardController.h"
#include "MouseController.h"
#include "Inventory.h"

//Include GLFW
#include <GLFW/glfw3.h>

void Vine::interact(Player& Player)
{
	if (Inventory::GetInstance().findItem("scissor")) {
		setCurrDialogue(2);
		return;
	}
	setCurrDialogue(0);
	return;
}

void Vine::nextDialogue()
{
	if (getCurrDialogue() != nullptr) {
		if (Inventory::GetInstance().findItem("scissor")) {
			if (getCurrDialogue()->id < 1) {

				setCurrDialogue(getCurrDialogue()->id + 1);
			}
			else { setCurrDialogue(-1); }
		}
		else {
			if (getCurrDialogue()->id < 4) {

				setCurrDialogue(getCurrDialogue()->id + 1);
			}
			else { setCurrDialogue(-1); }
		}
	}
}

float Vine::getRadius()
{
	return radius;
}

Vine::Vine(Vector3 Position) : InteractableObject("Vine", Position)
{
	radius = 3.f;
}

Vine::~Vine()
{
}

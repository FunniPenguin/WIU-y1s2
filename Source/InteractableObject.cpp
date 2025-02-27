#include "InteractableObject.h"
#include <fstream>
#include <iostream>
#include <sstream>

void InteractableObject::interact(Player& Player)
{
	currDialogue = dialogues[0];
}

Dialogue* InteractableObject::getCurrDialogue() const
{
	return currDialogue;
}

void InteractableObject::nextDialogue()
{
	if (currDialogue != nullptr) {
		if (currDialogue->id < numDialogues - 1) {

			currDialogue = dialogues[currDialogue->id + 1];
		}
		else { currDialogue = nullptr; }
	}
}

std::string InteractableObject::getObjName() const
{
	return objName;
}

void InteractableObject::loadDialogues()
{
	std::ifstream inputFile("textFiles//GameScript.txt");
	std::string line, text;
	bool read = false;
	int index = 0;
	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line)) {
			if (read) {
				std::stringstream ss(line);
				std::getline(ss, text, ';');
				if (text == "numDialogues") {
					std::getline(ss, text, ';');
					numDialogues = stoi(text);
					dialogues = new Dialogue*[numDialogues];
				}
				else if (text == "end") {
					read = false;
				}
				else {
					dialogues[index] = new Dialogue;
					dialogues[index]->text = text;
					std::getline(ss, text, ';');
					dialogues[index]->id = stoi(text);
					index++;
				}
			}
			else {
				if (line == objName) {
					read = true;
				}
			}
		}
	}
	else { std::cout << "Error opening text file."; }
	inputFile.close();
}

void InteractableObject::setCurrDialogue(int index)
{
	if (index < 0) {
		currDialogue = nullptr; return;
	}
	currDialogue = getDialogues(index);
}

Dialogue* InteractableObject::getDialogues(int index)
{
	return dialogues[index];
}

InteractableObject::InteractableObject(std::string Name) : GameObject()
{
	objName = Name;
	currDialogue = nullptr;
	loadDialogues();
}

InteractableObject::InteractableObject(std::string Name, Vector3 Position) : GameObject(Position)
{
	objName = Name;
	currDialogue = nullptr;
	loadDialogues();
}

InteractableObject::~InteractableObject()
{
	for (int i = 0; i < numDialogues; i++) {
		if (dialogues[i] != nullptr) {
			delete dialogues[i];
		}
	}
}

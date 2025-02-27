#include "Inventory.h"
#include <fstream>
#include <sstream>

Inventory& Inventory::GetInstance()
{
	static Inventory instance; //Note that this will always be the same scene manager that is returned
	return instance;
}

void Inventory::addItem(std::string ItemName)
{
	std::ifstream inputFile("textFiles//GameItems.txt");
	std::string line, text;
	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line)) {
			std::stringstream ss(line);
			std::getline(ss, text, ';');
			if (text == ItemName) {
				std::string description;
				std::getline(ss, text, ';');
				description = text;
				GameItem newItem;
				newItem.name = ItemName;
				newItem.description = description;
				p_Inventory.push_back(GameItem(newItem));
				//Check if inventory already has this item
				for (int i = 0; i < uniqueItems.size(); i++) {
					if (uniqueItems[i].name == ItemName) {
						inputFile.close();
						return; //If has the item, then no need to add to unique items as its not a new unique item
					}
				}
				uniqueItems.push_back(GameItem(newItem));
				inputFile.close();
				return;
			}
		}
	}
	else { std::cout << "Error opening text file."; }
	inputFile.close();
}

std::vector<GameItem>& Inventory::getInventory()
{
	return p_Inventory;
}

int Inventory::getNumUniqueItems()
{
	return uniqueItems.size();
}

GameItem Inventory::getItem() const
{
	return uniqueItems[currItemIndex];
}

int Inventory::getCurrItemIndex()
{
	return currItemIndex;
}

bool Inventory::moreThan1Item()
{
	int count = 0;
	for (int i = 0; i < p_Inventory.size(); i++) {
		if (p_Inventory[i].name == uniqueItems[currItemIndex].name) {
			count++;
		}
	}
	return (count > 1);
}

int Inventory::getItemQuantity()
{
	int count = 0;
	for (int i = 0; i < p_Inventory.size(); i++) {
		if (p_Inventory[i].name == uniqueItems[currItemIndex].name) {
			count++;
		}
	}
	return count;
}

bool Inventory::findItem(std::string ItemName)
{
	for (int i = 0; i < uniqueItems.size(); i++) {
		if (uniqueItems[i].name == ItemName) {
			return true;
		}
	}
	return false;
}

void Inventory::nextItem()
{
	currItemIndex++;
	if (currItemIndex >= uniqueItems.size())
		currItemIndex = uniqueItems.size() - 1;
}

void Inventory::prevItem()
{
	currItemIndex--;
	if (currItemIndex < 0)
		currItemIndex = 0;
}

void Inventory::Init()
{
	currItemIndex = 0;
}

void Inventory::Exit()
{
	
}


#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>

// <Note>
// This struct is for Game Items in a player's inevntory, meant to hold a name and a description
// Struct is public so that other objects can check if present in the struct
// Using struct because game items do not have much utility outside of being checks for interactions, they do not need functions
// <\Note>
struct GameItem {
	std::string name;
	std::string description;
};
class Inventory {
private:
	std::vector<GameItem> p_Inventory;
	std::vector<GameItem> uniqueItems;
	int currItemIndex;
public:
	Inventory() = default;
	~Inventory() {};
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	void Init();
	void Exit();

	static Inventory& GetInstance();
	void addItem(std::string ItemName);
	std::vector<GameItem>& getInventory();
	int getNumUniqueItems(); //returns size of vector uniqueItems
	GameItem getItem() const; //for displaying inventory to determine which item to diplay
	int getCurrItemIndex(); //returns the index of currItem in vector uniqueItems
	bool moreThan1Item(); //returns true if item is more than 1
	int getItemQuantity(); //returns quantity of currItem
	bool findItem(std::string ItemName);
	void nextItem();
	void prevItem();
};

#endif


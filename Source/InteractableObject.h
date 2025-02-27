#ifndef INTERACTABLE_OBJECT_H
#define INTERACTABLE_OBJECT_H

#include "GameObject.h"
#include "Player.h"

#include <fstream>
#include <vector>
//Vector class is from FORMOP, only extra thing added was conversion from Vector3 to glm::vec3 and contructor with glm::vec3
#include "Vector3.h"

struct Dialogue { //struct because I just want to group the dialogue data together, dialogues do not require functions
	int id;
	std::string text;
	Dialogue() { id = -1, text = "Err"; };
	Dialogue(int Id, std::string Text) {
		id = Id;
		text = Text;
	}
};

//Done by DylanYap, to be used for NPCs and game items
class InteractableObject : public GameObject
{
private:
	Dialogue** dialogues;
	std::string objName;
	Dialogue* currDialogue;
	int numDialogues;
	Dialogue* getDialogues(int index); //Private as I will not be using this outside of the class
	//Note: There is no need to create an item list as all interactable objects should only drop one item
	//Note: Even if they drop more than 1 item you can just hard code it
	//Note: For interactions in scene, have an interactable obj ptr to identify which obj is currently interacting with player
public:
	virtual void interact(Player& Player); //Sets the currDialogue to the first dialogue of the interaction. Add items to player inventory here.
	Dialogue* getCurrDialogue() const; //in update, check if current dialogue is nullptr to determine whether to unpause from dialogue
	virtual void nextDialogue(); //The current function assumes the obj will not have varying interactions with the player
	std::string getObjName() const;
	void loadDialogues(); //Read dialogues from text file and place into interactable obj
	void setCurrDialogue(int index);
	

	InteractableObject(std::string Name);
	InteractableObject(std::string Name, Vector3 Position);
	~InteractableObject();
};

#endif
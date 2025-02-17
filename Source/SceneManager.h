
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "BaseScene.h"

//Include all the scene enums here, comment your section so that it will be easier to integrate the code
enum SCENE_NUM {
	SCENE_START = 0,
	//Dylan enums
	SCENE_EXAMPLE,
	//Other people enums
	TOTAL_SCENE //Must be the last enum, do not touch or remove
};
class SceneManager
{
private:
	SCENE_NUM sceneNum;
	BaseScene* Scenes[static_cast<int>(TOTAL_SCENE)];
	BaseScene* currentScene;

public:
	//ensure an instance of this class can't be created outside of this class
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	static SceneManager& GetInstance(); //Accesses the scene manager and its functions
	void LoadScene(SCENE_NUM scene2Load); //Switches scenes
	void InitScene(SCENE_NUM startingSceneNum);
	BaseScene& GetCurrentScene();
	void Exit(); //Destructor

private:
	
};

#endif
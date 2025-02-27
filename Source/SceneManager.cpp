
#include "SceneManager.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

//Include all the scene files to use here
#include "SceneStart.h"
#include "SceneExample.h"
#include "SceneBallCup.h"
#include "SceneEnd.h"
#include "SceneDeath.h"

SceneManager::~SceneManager()
{
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance; //Note that this will always be the same scene manager that is returned
	return instance;
}


void SceneManager::InitScene(SCENE_NUM startingSceneNum)
{
	//Initiallise all the scenes in the array, just copy and paste and replace with new scene, change the enum
	Scenes[static_cast<int>(SCENE_START)] = new SceneStart();
	Scenes[static_cast<int>(SCENE_EXAMPLE)] = new SceneExample();
	Scenes[static_cast<int>(SCENE_BALLCUP)] = new SceneBallCup();
	Scenes[static_cast<int>(SCENE_END)] = new SceneEnd();
	Scenes[static_cast<int>(SCENE_LOSE)] = new SceneDeath();
	//Initialising the scene num and current scene, do not touch this
	sceneNum = startingSceneNum;
	currentScene = Scenes[static_cast<int>(sceneNum)];
	currentScene->Init();
}

BaseScene& SceneManager::GetCurrentScene()
{
	return *currentScene;
}

void SceneManager::LoadScene(SCENE_NUM scene2Load)
{
	//switches scenes
	sceneNum = scene2Load;
	currentScene->Exit();
	currentScene = Scenes[static_cast<int>(sceneNum)];
	currentScene->Init();
}

void SceneManager::Exit()
{
	currentScene->Exit();
	for (int i = 0; i < static_cast<int>(TOTAL_SCENE); i++) {
		if (Scenes[i] != nullptr) {
			delete Scenes[i];
		}
	}
}


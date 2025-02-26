#ifndef SCENE_BALLOONPOP_H
#define SCENE_BALLOONPOP_H

#include "BaseScene.h"
#include "Mesh.h"
#include "AltAzCamera.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

//GameObjects
#include "Dart.h"
#include "Ball.h"
#include "Cube.h"
#include "Eyeball.h"
#include "Player.h"
#include "Tree.h"

class SceneBalloonPop : public BaseScene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_CUBE,
		GEO_PLANE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_TEXT,
		GEO_STALL,
		GEO_EYEBALL,
		GEO_DART,
		GEO_METER,
		GEO_METER2,
		GEO_TIMEBAR,
		GEO_TEST,
		GEO_DOORWAY,
		GEO_TREE,
		GEO_RGATE,
		GEO_LGATE,
		NUM_GEOMETRY,
	};

	SceneBalloonPop() {};
	~SceneBalloonPop() {};

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
	void InitLights();

private:
	//Render functions
	void HandleKeyPress();
	void RenderSkybox();

	//meshlist
	Mesh* meshList[NUM_GEOMETRY];

	//Light settings
	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight, gameStart, inBooth, balloonpopLose;
	bool balloonpopVictory = false;

	//Game objects
	Ball* balls[50];
	float ballCD;
	
	Dart* darts[50];
	float dartCD;

	Cube* cubes[50];
	float cubeCD;
	
	Tree* trees[200];

	Eyeball* eyeballs[21];

	Player* player;

	FPCamera* fpcamera;
	
	int power, popcount;
	float time, gaterotate;
};

#endif
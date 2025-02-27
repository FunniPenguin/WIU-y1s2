#ifndef SCENE_BALLOONPOP_H
#define SCENE_BALLOONPOP_H

#include "BaseScene.h"
#include "Mesh.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

//GameObjects
#include "Dart.h"
#include "Eyeball.h"
#include "Player.h"
#include "DylanTree.h"
#include "Fence.h"
#include "Sign.h"
#include "TornRecordPage3.h"

class SceneBalloonPop : public BaseScene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_CUBE,
		GEO_QUAD,
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
		GEO_FENCE,
		GEO_SIGN,
		GEO_PAPER,
		GEO_PATH,
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
	void RenderInventory();

	//meshlist
	Mesh* meshList[NUM_GEOMETRY];

	//Light settings
	static const int NUM_LIGHTS = 3;
	Light light[NUM_LIGHTS];
	bool enableLight, gameStart, inBooth, balloonpopLose;
	bool balloonpopVictory = false;

	//Game objects
	
	Dart* darts[50];
	float dartCD;
	
	DylanTree* trees[70];

	Eyeball* eyeballs[21];

	Player* player;

	FPCamera* fpcamera;

	Fence* fence;
	
	TornRecordPage3* tornrecordpage3;
	bool pickedup_tornrecordpage3;

	Sign* sign;
	
	int power, popcount;
	float time, gaterotate;
};

#endif
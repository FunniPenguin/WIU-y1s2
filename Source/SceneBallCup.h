#ifndef SCENE_BALL_CUP_H
#define SCENE_BALL_CUP_H

#include "BaseScene.h"
#include "Mesh.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

//GameObjects
#include "Ball.h"
#include "InteractableObject.h"
#include "Newspaper.h"
#include "Player.h"
#include "Fence.h"
#include "Sign.h"
#include "jar.h"
#include "DylanTree.h"

class SceneBallCup : public BaseScene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_CUBE,
		GEO_QUAD,
		GEO_STONEFLOOR,
		GEO_BLOOD,
		GEO_NEWSPAPER,
		GEO_TREE,
		GEO_FENCE,
		GEO_SIGN,
		GEO_JAR,
		GEO_STONETABLET,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_TEXTBOX,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	SceneBallCup();
	~SceneBallCup();

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
	InteractableObject* currInteraction;

	//Light settings
	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight;

	//Game objects
	Ball* balls[5];
	float ballCD;

	DylanTree* trees[69];

	static const int NUM_IOBJS= 3;
	InteractableObject* interactableObjs[NUM_IOBJS]; //for interactable objs that do not place items into player inventory

	Jar* jars[3];

	Newspaper* newspaper;
	bool pickedup_newspaper;

	Sign* sign;
};

#endif
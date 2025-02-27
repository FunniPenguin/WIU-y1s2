#ifndef SCENE_END_H
#define SCENE_END_H

#include "BaseScene.h"
#include "Mesh.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

//GameObjects
#include "Player.h"

class SceneEnd : public BaseScene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_CUBE,
		GEO_QUAD,
		GEO_PLANE,
		GEO_GRASSFLOOR,
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

	SceneEnd() {};
	~SceneEnd() {};

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
	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight;

	//Game variables
	bool playerWin;
};

#endif
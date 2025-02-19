#ifndef SCENE_EXAMPLE_H
#define SCENE_EXAMPLE_H

#include "BaseScene.h"
#include "Mesh.h"
#include "AltAzCamera.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

//GameObjects
#include "Ball.h"
#include "Cube.h"
#include "Ground.h"

class SceneExample : public BaseScene
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
		NUM_GEOMETRY,
	};

	SceneExample() {};
	~SceneExample() {};

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
	bool enableLight;

	//Game objects
	Ball* balls[50];
	float ballCD;

	Ground* ground;

	Cube* cubes[50];
	float cubeCD;
};

#endif
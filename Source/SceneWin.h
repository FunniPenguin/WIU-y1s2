#ifndef SCENE_WIN_H
#define SCENE_WIN_H

#include "BaseScene.h"
#include "Mesh.h"
#include "FPCamera.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneWin : public BaseScene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_CUBE,
		GEO_PLANE,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	SceneWin() {};
	~SceneWin() {};

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
	void InitLights();
private:
	void HandleKeyPress();
	Mesh* meshList[NUM_GEOMETRY];
	//For the start screen I do not want the objects to have depth so I set projection type to 0
	int projType = 0; // fix to 0 for orthographic, 1 for projection

	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight;
};

#endif
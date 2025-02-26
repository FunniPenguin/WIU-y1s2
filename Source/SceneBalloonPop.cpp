#include "SceneBalloonPop.h"
#include "GL\glew.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

//Include GLFW
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "MouseController.h"
#include "KeyboardController.h"
#include "LoadTGA.h"
#include "SceneManager.h"

//Physics functions
#include "CollisionDetection.h"

void SceneBalloonPop::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	/*glEnable(GL_CULL_FACE);*/

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shader programs
	//m_programID = LoadShaders("Shader//Texture.vertexshader",
		//"Shader//Texture.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader",
		"Shader//Text.fragmentshader");
	glUseProgram(m_programID);
	
	//Initialise the lights in a function so that code is more organised
	InitLights();

	// Initialise camera properties
	camera.Init(glm::vec3(4, 10, 3), glm::vec3(0, 0, 0));

	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", glm::vec3(1.f, 1.f, 1.f), 1.f, 16, 16);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PLANE] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PLANE]->textureID = LoadTGA("Images//grass.tga");
	meshList[GEO_METER] = MeshBuilder::GenerateQuad("Meter", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_METER]->textureID = LoadTGA("Images//white.tga");
	meshList[GEO_METER2] = MeshBuilder::GenerateQuad("Meter2", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_METER2]->textureID = LoadTGA("Images//black.tga");
	meshList[GEO_TIMEBAR] = MeshBuilder::GenerateQuad("TimeBar", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_TIMEBAR]->textureID = LoadTGA("Images//red.tga");

	//Generate skybox
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Images//nightsky_lf.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Images//nightsky_rt.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Images//nightsky_up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Images//nightsky_dn.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Images//nightsky_bk.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 200.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Images//nightsky_ft.tga");
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ( "tree", "Models//PineTree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Images//tree.tga");

	// For models with mtl files, put models below the following line
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR],	m_parameters[U_MATERIAL_SHININESS]);

	meshList[GEO_EYEBALL] = MeshBuilder::GenerateOBJMTL("eyeball", "Models//eyeball.obj", "Models//eyeball.mtl");
	meshList[GEO_EYEBALL]->textureID = LoadTGA("Images//eyeball.tga");	

	meshList[GEO_STALL] = MeshBuilder::GenerateOBJMTL("stall", "Models//stall.obj", "Models//stall.mtl");
	meshList[GEO_STALL]->textureID = LoadTGA("Images//stallbloody.tga");

	meshList[GEO_DART] = MeshBuilder::GenerateOBJMTL("dart", "Models//dart.obj", "Models//dart.mtl");
	meshList[GEO_DART]->textureID = LoadTGA("Images//dart.tga");

	meshList[GEO_DOORWAY] = MeshBuilder::GenerateOBJMTL("doorway", "Models//doorway.obj", "Models//doorway.mtl");
	meshList[GEO_DOORWAY]->textureID = LoadTGA("Images//doorway.tga");

	meshList[GEO_RGATE] = MeshBuilder::GenerateOBJMTL("rgate", "Models//rgate.obj", "Models//rgate.mtl");
	meshList[GEO_RGATE]->textureID = LoadTGA("Images//gate.tga");
	meshList[GEO_LGATE] = MeshBuilder::GenerateOBJMTL("lgate", "Models//lgate.obj", "Models//lgate.mtl");
	meshList[GEO_LGATE]->textureID = LoadTGA("Images//gate.tga");

	meshList[GEO_TEST] = MeshBuilder::GenerateOBJMTL("test", "Models//scarecrow.obj", "Models//scarecrow.mtl");
	meshList[GEO_TEST]->textureID = LoadTGA("Images//scarecrowpng.tga");

	// 16 x 16 is the number of columns and rows for the text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Images//calibri.tga");

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	enableLight = true;
	inBooth = true;	// set to true for debug, set to false later
	balloonpopLose = false;
	popcount = 0;
	time = 45.f;

	//Game variables
	for (int i = 0; i < 50;i++) {
		balls[i] = nullptr;
	}
	for (int i = 0; i < 21; i++) {
		eyeballs[i] = nullptr;
	}
	for (int i = 0; i < 50; i++) {
		darts[i] = nullptr;
	}
	ballCD = 0;
	for (int i = 0; i < 50;i++) {
		cubes[i] = nullptr;
	}
	cubeCD = 0;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 3; j++) {
			eyeballs[i + j*7] = new Eyeball(Vector3(-12.5f, 12.f - 3 * j, -6.f + 2 * i), 1.5f, 0);
		}
	}

	player = new Player(Vector3(23.5, 10, 0));
	camera.Init((player->getPosition() + Vector3{ 1.f, 0.f, 0.f }).convert2glm(),
		(player->getPosition() + Vector3{ 2.f, 0.f, 0.f }).convert2glm());

	//outer ring of trees
	for (int i = 0; i < 11; i++) 
		trees[i] = new Tree(Vector3(100 - i * 20, 0, 100), 1.f, 0);
	for (int i = 0; i < 11; i++)
		trees[i + 11] = new Tree(Vector3(100 - i * 20, 0, -100), 1.f, 0);
	for (int i = 0; i < 4; i++)
		trees[i + 22] = new Tree(Vector3(100, 0, 80 - i * 20), 1.f, 0);
	for (int i = 0; i < 4; i++)
		trees[i + 26] = new Tree(Vector3(100, 0, -80 + i * 20), 1.f, 0);
	for (int i = 0; i < 4; i++)
		trees[i + 30] = new Tree(Vector3(-100, 0, 80 - i * 20), 1.f, 0);
	for (int i = 0; i < 4; i++)
		trees[i + 34] = new Tree(Vector3(-100, 0, -80 + i * 20), 1.f, 0);

	// inner ring of trees
	for (int i = 0; i < 10; i++)
		trees[i + 38] = new Tree(Vector3(90 - i * 20, 0, 90), 1.f, 0);
	for (int i = 0; i < 10; i++)
		trees[i + 48] = new Tree(Vector3(90 - i * 20, 0, -90), 1.f, 0);
	for (int i = 0; i < 3; i++)
		trees[i + 58] = new Tree(Vector3(90, 0, 70 - i * 20), 1.f, 0);
	for (int i = 0; i < 3; i++)
		trees[i + 61] = new Tree(Vector3(90, 0, -70 + i * 20), 1.f, 0);
	for (int i = 0; i < 3; i++)
		trees[i + 64] = new Tree(Vector3(-90, 0, 70 - i * 20), 1.f, 0);
	for (int i = 0; i < 3; i++)
		trees[i + 67] = new Tree(Vector3(-90, 0, -70 + i * 20), 1.f, 0);
	 
	
	//for (int i = 0; i < 10; i++)
	//	trees[i + 10] = new Tree(Vector3(50 - i * 10, 0, -50), 1.f, 0);
	//	trees[20] = new Tree(Vector3(50, 0, 50), 1.f, 0);
	//	trees[21] = new Tree(Vector3(50, 0, 40), 1.f, 0);
	//	trees[22] = new Tree(Vector3(50, 0, 30), 1.f, 0);
	//	trees[23] = new Tree(Vector3(50, 0, 20), 1.f, 0);
	//	trees[24] = new Tree(Vector3(50, 0, 10), 1.f, 0);
	//	trees[25] = new Tree(Vector3(50, 0, -10), 1.f, 0);
	//	trees[26] = new Tree(Vector3(50, 0, -20), 1.f, 0);
	//	trees[27] = new Tree(Vector3(50, 0, -30), 1.f, 0);
	//	trees[28] = new Tree(Vector3(50, 0, -40), 1.f, 0);
	//	trees[29] = new Tree(Vector3(50, 0, -50), 1.f, 0);
	//for (int i = 0; i < 10; i++)
	//	trees[i + 30] = new Tree(Vector3(-50, 0, 40 - i * 10), 1.f, 0);

	//for (int i = 0; i < 9; i++)
	//	trees[i + 40] = new Tree(Vector3(45 - i * 10, 0, 45), 1.f, 0);
	//for (int i = 0; i < 9; i++)
	//	trees[i + 50] = new Tree(Vector3(45 - i * 10, 0, -45), 1.f, 0);
	//trees[60] = new Tree(Vector3(45, 0, 45), 1.f, 0);
	//trees[61] = new Tree(Vector3(45, 0, 35), 1.f, 0);
	//trees[62] = new Tree(Vector3(45, 0, 25), 1.f, 0);
	//trees[63] = new Tree(Vector3(45, 0, 15), 1.f, 0);
	//trees[64] = new Tree(Vector3(45, 0, -15), 1.f, 0);
	//trees[65] = new Tree(Vector3(45, 0, -25), 1.f, 0);
	//trees[66] = new Tree(Vector3(45, 0, -35), 1.f, 0);
	//trees[67] = new Tree(Vector3(45, 0, -45), 1.f, 0);
	//for (int i = 0; i < 9; i++)
	//	trees[i + 70] = new Tree(Vector3(-45, 0, 45 - i * 10), 1.f, 0);
	// 
	// this tree generation code sucks ass
}

void SceneBalloonPop::Update(double dt)
{
	HandleKeyPress();
	
	// handle gamestart
	if (player->getPosition().x < 5 && player->getPosition().x > -5 && player->getPosition().z < 5 && player->getPosition().z > -5) {
		if (KeyboardController::GetInstance()->IsKeyPressed('E')) {
			gameStart = true;
		}
	}
	
	// handle outer collision
		if (player->getPosition().x > 80) {
			player->setObjectPosition(glm::vec3(80, player->getPosition().y, player->getPosition().z));
			camera.position.x = player->getPosition().x;
		}
		if (player->getPosition().x < -80) {
			player->setObjectPosition(glm::vec3(-80, player->getPosition().y, player->getPosition().z));
			camera.position.x = player->getPosition().x;
		}
		if (player->getPosition().z > 80) {
			player->setObjectPosition(glm::vec3(player->getPosition().x, player->getPosition().y, 80));
			camera.position.z = player->getPosition().z;
		}
		if (player->getPosition().z < -80) {
			player->setObjectPosition(glm::vec3(player->getPosition().x, player->getPosition().y, -80));
			camera.position.z = player->getPosition().z;
		}
	
	// if win, can leave
	if (KeyboardController::GetInstance()->IsKeyPressed('E') && balloonpopVictory == true && player->getPosition().x < -75 && player->getPosition().x > -85 && player->getPosition().z < 5 && player->getPosition().z > -5) {
		SceneManager::GetInstance().LoadScene(SCENE_BALLOONPOP);  	// CHANGE TO WHATEVER SCENE YOU WANT NEXT
		return;
	}
	// if lose, go to scenedeath
	if (time <= 0) {
		if (balloonpopVictory == false)
			balloonpopLose = true;
		gameStart = false;
		time = 45.f;
		popcount = 0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 3; j++) {
				eyeballs[i + j * 7] = new Eyeball(Vector3(-12.5f, 12.f - 3 * j, -6.f + 2 * i), 1.5f, 0);
			}
		}
	}

	if (balloonpopLose == true) {
		SceneManager::GetInstance().LoadScene(SCENE_DEATH);
		return;
	}

	dartCD -= dt;

	if (KeyboardController::GetInstance()->IsKeyDown('I'))
		light[0].position.z -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('K'))
		light[0].position.z += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('J'))
		light[0].position.x -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('L'))
		light[0].position.x += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('O'))
		light[0].position.y -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('P'))
		light[0].position.y += static_cast<float>(dt) * 5.f;
	if (MouseController::GetInstance()->IsButtonPressed(0) && (dartCD <= 0.f) && gameStart == true) {
		if (power < 100) {
			power++;
		}
	}
	if (MouseController::GetInstance()->IsButtonReleased(0) && (dartCD <= 0.f) && gameStart == true) {
		for (int i = 0; i < 50; i++) {
			if (darts[i] == nullptr) {
				darts[i] = new Dart{ camera.position, 0.5, 10 };
				darts[i]->AddImpulse(Vector3(normalize(camera.target - camera.position)) * power);
				dartCD = 1.f;
				power = 0;
				break;
			}
		}
	}
	for (int i = 0; i < 50; i++) {
		if (darts[i] != nullptr) {
			// ball collision
			OverlapSphere2Ground(*darts[i], darts[i]->getHitbox().getRadius(), 00);
			for (int i = 0; i < 50; i++) {
				if (darts[i] != nullptr) {
					for (int j = 0; j < 21; j++) {
						if (eyeballs[j] != nullptr) {
							CollisionData cd;
							if (OverlapSphere2Sphere(*darts[i], darts[i]->getHitbox().getRadius(), *eyeballs[j], eyeballs[j]->getHitbox().getRadius(), cd)) {
								delete eyeballs[j];
								eyeballs[j] = nullptr;
								delete darts[i];
								darts[i] = nullptr;
								popcount++;
								break;
							}
						}
					}
				}
			}

			// check for win
			if (popcount == 21) {
				balloonpopVictory = true;
				gameStart = false;
				time = 45.f;
				popcount = 0;
				for (int i = 0; i < 7; i++) {
					for (int j = 0; j < 3; j++) {
						eyeballs[i + j * 7] = new Eyeball(Vector3(-12.5f, 12.f - 3 * j, -6.f + 2 * i), 1.5f, 0);
					}
				}
			}

			for (int i = 0; i < 21; i++) {
				if (eyeballs[i] != nullptr) {
					eyeballs[i]->UpdatePhysics(dt);
				}
			}
			for (int i = 0; i < 50; i++) {
				if (darts[i] != nullptr) {
					darts[i]->UpdatePhysics(dt);
				}
			}
			for (int i = 0; i < 50; i++) {
				if (darts[i] != nullptr) {
					if ((darts[i]->getPosition().x > 50) || (darts[i]->getPosition().x < -50) ||
						(darts[i]->getPosition().y > 50) || (darts[i]->getPosition().y < 1) ||
						(darts[i]->getPosition().z > 50) || (darts[i]->getPosition().z < -50)) {
						delete darts[i];
						darts[i] = nullptr;
					}
				}
			}
		}
	}

	player->movePlayer(dt, camera);
	player->UpdatePhysics(dt, camera);
	camera.Update(dt);

	// gates swing open when you approach if game is cleared
	if (balloonpopVictory == true) {
		if (player->getPosition().x < -50 && gaterotate < 60) {
			gaterotate += dt * 30;
		}
	}

	if (gameStart == true)
		time -= dt;
}

void SceneBalloonPop::Render()
{
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load view matrix stack and set it with camera position, target position and up direction
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	// Load identity matrix into the model stack
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		glm::vec3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		glm::vec3 lightDirection_cameraspace = viewStack.Top() * glm::vec4(lightDir, 0);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightDirection_cameraspace));
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[0].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightPosition_cameraspace));
		glm::vec3 spotDirection_cameraspace = viewStack.Top() * glm::vec4(light[0].spotDirection, 0);
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, glm::value_ptr(spotDirection_cameraspace));
	}
	else {
		// Calculate the light position in camera space
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[0].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightPosition_cameraspace));
	}
	//Skybox first so it is not affected by stack errors
	RenderSkybox();

	// Render objects
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	// Render light
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_SPHERE], false);
	modelStack.PopMatrix();

	meshList[GEO_DART]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_DART]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_DART]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_DART]->material.kShininess = 1.0f;
	for (int i = 0; i < 50; i++) {
		if (darts[i] != nullptr) {
			modelStack.PushMatrix();
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Translate(darts[i]->getPosition().x, darts[i]->getPosition().y, darts[i]->getPosition().z);
			modelStack.Scale(0.3f, 0.3f, 0.3f);
			RenderMesh(meshList[GEO_DART], true);
			modelStack.PopMatrix();
		}
	}
	for (int i = 0; i < 50; i++) {
		if (cubes[i] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(cubes[i]->getPosition().x, cubes[i]->getPosition().y, cubes[i]->getPosition().z);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_CUBE], false);
			modelStack.PopMatrix();
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(100.f - 50 * i, 0.f, 100.f - 50 * j);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(50.f, 50.f, 1.f);
			meshList[GEO_PLANE]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
			meshList[GEO_PLANE]->material.kDiffuse = glm::vec3(1, 1, 1);
			meshList[GEO_PLANE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
			meshList[GEO_PLANE]->material.kShininess = 1.0f;
			RenderMesh(meshList[GEO_PLANE], true);
			modelStack.PopMatrix();
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (trees[i] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(trees[i]->getPosition().x, trees[i]->getPosition().y, trees[i]->getPosition().z);
			modelStack.Scale(20.f, 30.f, 20.f);
			meshList[GEO_TREE]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
			meshList[GEO_TREE]->material.kDiffuse = glm::vec3(1, 1, 1);
			meshList[GEO_TREE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
			meshList[GEO_TREE]->material.kShininess = 1.0f;
			RenderMesh(meshList[GEO_TREE], true);
			modelStack.PopMatrix();
		}
	}
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	meshList[GEO_STALL]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_STALL]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_STALL]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_STALL]->material.kShininess = 1.0f;
	RenderMesh(meshList[GEO_STALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-90.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6.5f, 3.5f, 6.5f);
	meshList[GEO_DOORWAY]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_DOORWAY]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_DOORWAY]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_DOORWAY]->material.kShininess = 1.0f;
	RenderMesh(meshList[GEO_DOORWAY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-90.f, 0.f, 11.f);
	modelStack.Rotate(90 + gaterotate, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	meshList[GEO_LGATE]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_LGATE]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_LGATE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_LGATE]->material.kShininess = 1.0f;
	RenderMesh(meshList[GEO_LGATE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-90.f, 0.f, -11.f);
	modelStack.Rotate(90 - gaterotate, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	meshList[GEO_RGATE]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_RGATE]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_RGATE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_RGATE]->material.kShininess = 1.0f;
	RenderMesh(meshList[GEO_RGATE], true);
	modelStack.PopMatrix();

	meshList[GEO_EYEBALL]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_EYEBALL]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_EYEBALL]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_EYEBALL]->material.kShininess = 1.0f;
	for (int i = 0; i < 21; i++)
	{
		if (eyeballs[i] != nullptr) {
			modelStack.PushMatrix();
			//dist between each ball is 2
			modelStack.Translate(-12.5f, eyeballs[i]->getPosition().y, eyeballs[i]->getPosition().z);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			RenderMesh(meshList[GEO_EYEBALL], true);
			modelStack.PopMatrix();
		}
	}

	if (camera.cameraState != FIRST_PERSON) {
		modelStack.PushMatrix();
		modelStack.Translate(player->getPosition().x, player->getPosition().y, player->getPosition().z);
		meshList[GEO_PLANE]->material.kAmbient = glm::vec3(0.5, 0.7, 0.5);
		meshList[GEO_PLANE]->material.kDiffuse = glm::vec3(1, 1, 1);
		meshList[GEO_PLANE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
		meshList[GEO_PLANE]->material.kShininess = 1.0f;
		modelStack.Scale(player->getHitbox().getHalfDimensions().x * 2, player->getHitbox().getHalfDimensions().y * 2, player->getHitbox().getHalfDimensions().z * 2);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	}

	if (gameStart == true)
	{
		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_METER2], 400, 600, time * 20 + 5, 40);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_TIMEBAR], 400, 600, time * 20, 35);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_METER2], 400, 100, power + 2, 12);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_METER], 400, 100, power, 10);
		modelStack.PopMatrix();


	}

	// gamestart prompt
	if (player->getPosition().x < 5 && player->getPosition().x > -5 && player->getPosition().z < 5 && player->getPosition().z > -5 && gameStart == false) {
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to start.", glm::vec3(1, 1, 1), 0.5, 20.0f, 10.0f, 10.0f);
		modelStack.PopMatrix();
	}

	// leave prompt
	if (player->getPosition().x < -75 && player->getPosition().x > -85 && player->getPosition().z < 5 && player->getPosition().z > -5 ) {
		if (balloonpopVictory == true) {
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to leave.", glm::vec3(1, 1, 1), 0.5, 20.0f, 10.0f, 10.0f);
			modelStack.PopMatrix();
		}
		if (balloonpopVictory == false) {
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "The gates won't budge...", glm::vec3(1, 1, 1), 0.5, 20.0f, 10.0f, 10.0f);
			modelStack.PopMatrix();
		}
	}
	std::cout << "Player Position: " << player->getPosition().x << " " << player->getPosition().y << " " << player->getPosition().z << std::endl;
}

void SceneBalloonPop::Exit()
{
	//Game variables cleanup
	for (int i = 0; i < 50; i ++) {
		if (balls[i] != nullptr) {
			delete balls[i];
		}
	}
	for (int i = 0; i < 200; i++) {
		if (trees[i] != nullptr) {
			delete trees[i];
		}
	}
	for (int i = 0; i < 50; i++) {
		if (darts[i] != nullptr) {
			delete darts[i];
		}
	}
	for (int i = 0; i < 21; i++) {
		if (eyeballs[i] != nullptr) {
			delete eyeballs[i];
		}
	}
	if (player != nullptr) {
		delete player;
	}
	for (int i = 0; i < 50; i++) {
		if (cubes[i] != nullptr) {
			delete cubes[i];
		}
	}
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneBalloonPop::HandleKeyPress()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_ENTER))
	{
		// Change camera type
		if (camera.cameraState == FIRST_PERSON) {
			camera.target = player->getPosition().convert2glm();
			camera.cameraState = THIRD_PERSON;
		}
		else if (camera.cameraState == THIRD_PERSON) {
			//Vector3 cameraOffset{ player->getPosition().Normalize().x, 0, player->getPosition().Normalize().z };
			camera.position = (player->getPosition()).convert2glm();
			camera.target = (player->getPosition() + Vector3{ 0.f, 0.f, 1.f }).convert2glm();
			camera.cameraState = FIRST_PERSON;
		}
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x31))
	{
		// Key press to enable culling
		glEnable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x32))
	{
		// Key press to disable culling
		glDisable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x33))
	{
		// Key press to enable fill mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x34))
	{
		// Key press to enable wireframe mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		// Change to black background
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void SceneBalloonPop::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, -100.f);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	// Offset in Z direction by 50 units
	modelStack.Translate(0.f, 0.f, 100.f);
	modelStack.Rotate(180, 0, 1, 0);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, -1, 0);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	// Offset in X direction by 50 units
	modelStack.Translate(-100.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	// Offset in Y direction by -50 units
	modelStack.Translate(0.f, 100.f, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 3);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PushMatrix();

	// Offset in Y direction by -50 units
	modelStack.Translate(0.f, -100.f, 0.f);
	modelStack.Rotate(90, -1, 0, 0);
	// Skybox should be rendered without light
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneBalloonPop::InitLights()
{
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	//Start of copy paste to add new lights
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	//End of copy paste, remeber to change the number in the enum and the string
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	//Do not touch this line of code
	glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);

	//Light 1
	light[0].position = glm::vec3(0, 5, 0);
	light[0].color = glm::vec3(1, 1, 1);
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = 45.f;
	light[0].cosInner = 30.f;
	light[0].exponent = 3.f;
	light[0].spotDirection = glm::vec3(0.f, 1.f, 0.f);

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], cosf(glm::radians<float>(light[0].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], cosf(glm::radians<float>(light[0].cosInner)));
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
}
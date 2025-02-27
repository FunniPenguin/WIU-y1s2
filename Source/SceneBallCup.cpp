#include "SceneBallCup.h"
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
#include "SoundManager.h"
#include "Inventory.h"

//Physics functions
#include "CollisionDetection.h"

SceneBallCup::SceneBallCup()
{
	//TODO: read from save file if 
}

void SceneBallCup::Init()
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

	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", glm::vec3(1.f, 1.f, 1.f), 1.f, 16, 16);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_STONEFLOOR] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_STONEFLOOR]->textureID = LoadTGA("Images//MedivalFloor.tga");
	meshList[GEO_BLOOD] = MeshBuilder::GenerateQuad("Blood", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_BLOOD]->textureID = LoadTGA("Images//Blood.tga");
	meshList[GEO_NEWSPAPER] = MeshBuilder::GenerateQuad("Newspaper", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_NEWSPAPER]->textureID = LoadTGA("Images//newspaper1.tga");
	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_TEXTBOX]->textureID = LoadTGA("Images//textBox.tga");

	//Generate objs
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "Models//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Images//tree.tga");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJMTL("Fence", "Models//oldfence.obj", "Models//oldfence.mtl");
	meshList[GEO_FENCE]->textureID = LoadTGA("Images//oldfence.tga");
	meshList[GEO_SIGN] = MeshBuilder::GenerateOBJMTL("Sign", "Models//sign.obj", "Models//sign.mtl");
	meshList[GEO_SIGN]->textureID = LoadTGA("Images//sign.tga");
	meshList[GEO_JAR] = MeshBuilder::GenerateOBJMTL("Jar", "Models//jar.obj", "Models//jar.mtl");
	meshList[GEO_JAR]->textureID = LoadTGA("Images//jar.tga");

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

	// For models with mtl files, put models below the following line
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR],	m_parameters[U_MATERIAL_SHININESS]);

	// 16 x 16 is the number of columns and rows for the text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Images//calibri.tga");

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	enableLight = true;

	//Game variables
	currGameState = RUNNING;
	currInteraction = nullptr;
	if (!pickedup_newspaper) {
		newspaper = new Newspaper(Vector3(-27.f, 0.1f, 13.f), "Newspaper1");
	}
	else { newspaper = nullptr; }
	for (int i = 0; i < 5;i++) {
		balls[i] = nullptr; //may want to mannually init the balls
	}
	jars[0] = new Jar(glm::vec3{ -5, 0.f, 7.5f });
	jars[1] = new Jar(glm::vec3{ -5, 0.f, -7.5f });
	jars[2] = new Jar(glm::vec3{ 5, 0.f, 0.f });
	for (int i = 0; i < 69; i++) {
		trees[i] = nullptr;
	}
	for (int i = 0; i < 8; i++) {
		trees[i] = new DylanTree(Vector3{ -35.f + (i * 7), 0, -35.f });
		trees[i + 8] = new DylanTree(Vector3{ 35.f - (i * 7), 0, 35.f });
		trees[i + 16] = new DylanTree(Vector3{ 35.f, 0, -35.f + (i * 7) });
		trees[i + 24] = new DylanTree(Vector3{ -35.f, 0, 35.f - (i * 7) });
	}
	ballCD = 0;
	interactionCD = 0;
	player = new Player(Vector3(-30, 1, 0));
	sign = new Sign{ Vector3(-13, 0, -13), "Sign4" };
	interactableObjs[0] = new InteractableObject{ "Ancient stone tablet", glm::vec3(-27, 0, 0)};
	// Initialise camera properties
	camera.Init((player->getPosition() + Vector3{ 1.f, 0.f, 0.f }).convert2glm(),
		(player->getPosition() + Vector3{ 2.f, 0.f, 0.f }).convert2glm());
	SoundManager::GetInstance().setBGM(BGM3);
}

void SceneBallCup::Update(double dt)
{
	HandleKeyPress();
	interactionCD -= dt;
	if (currGameState == RUNNING) {
		if (KeyboardController::GetInstance()->IsKeyPressed('Q')) {
			SceneManager::GetInstance().LoadScene(SCENE_END);
			return;
		}
		//Handle player-obj interactions
		if (interactionCD <= 0.f){
			if (KeyboardController::GetInstance()->IsKeyPressed('E')) {
				if (newspaper != nullptr) {
					if ((newspaper->getPosition() - player->getPosition()).Length() < newspaper->getRadius()) {
						newspaper->interact(*player);
						currInteraction = newspaper;
						currGameState = DIALOGUE;
						interactionCD = 1.5f;
						return;
					}
				}
				if (sign != nullptr) {
					if ((sign->getPosition() - player->getPosition()).Length() < sign->getRadius()) {
						sign->interact(*player);
						currInteraction = sign;
						currGameState = DIALOGUE;
						interactionCD = 1.5f;
						return;
					}
				}
			}
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('M')) {
			SoundManager::GetInstance().switchBGM(BGM3);
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('N')) {
			SoundManager::GetInstance().switchBGM(BGM4);
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('R')) {
			for (int i = 0; i < Inventory::GetInstance().getInventory().size(); i++) {
				std::cout << Inventory::GetInstance().getInventory()[i].name << i << ":\n";
				std::cout << Inventory::GetInstance().getInventory()[i].description << "\n";
			}
		}
		CollisionData cd;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//                                                  Ball collisions                                                   //
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 5; i++) {
			if (balls[i] != nullptr) {
				OverlapSphere2Ground(*balls[i], balls[i]->getHitbox().getRadius(), 0.f);
				if (OverlapSphere2Cube(*balls[i], balls[i]->getHitbox(), *player, player->getHitbox(), cd)) {
					ResolveCollision(cd);
				}
				for (int j = i + 1; j < 5; j++) {
					if (balls[j] != nullptr) {
						if (OverlapSphere2Sphere(*balls[i], balls[i]->getHitbox().getRadius(), *balls[j], balls[j]->getHitbox().getRadius(), cd))
							ResolveCollision(cd);
					}
				}
				balls[i]->UpdatePhysics(dt);
				if ((balls[i]->getPosition().x > 12.5) || (balls[i]->getPosition().x < -12.5) ||
					(balls[i]->getPosition().y > 12.5) ||
					(balls[i]->getPosition().z > 12.5) || (balls[i]->getPosition().z < -12.5)) {
					delete balls[i];
					balls[i] = nullptr;
				}
			}
		}
		player->movePlayer(dt, camera);
		//std::cout << player->getPosition().x << "|" << player->getPosition().y << "|" << player->getPosition().z << "|" << std::endl;
		player->UpdatePhysics(dt, camera);
		camera.Update(dt);
		//Update sounds
		SoundManager::GetInstance().updateSounds(dt);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                  Dialogue state                                                    //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (currGameState == DIALOGUE) {
		if (interactionCD <= 0.f) {
			if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_SPACE) ||
				KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_X) ||
				KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT_SHIFT) ||
				KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_E) ||
				MouseController::GetInstance()->IsButtonPressed(0) ||
				MouseController::GetInstance()->IsButtonPressed(1)) {
				currInteraction->nextDialogue();
				interactionCD = 1.5f;
				if (currInteraction->getCurrDialogue() == nullptr) {
					currGameState = RUNNING;
					delete newspaper;
					newspaper = nullptr;
					pickedup_newspaper = true;
					return;
				}
			}
		}
	}
	else if (currGameState == INVENTORY) {
		if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_RIGHT) ||
			KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_D)) {
			Inventory::GetInstance().nextItem();
		}
		else if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT) ||
			KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_A)) {
			Inventory::GetInstance().prevItem();
		}
	}
}

void SceneBallCup::Render()
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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                Render ground                                                       //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	meshList[GEO_STONEFLOOR]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
	meshList[GEO_STONEFLOOR]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_STONEFLOOR]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_STONEFLOOR]->material.kShininess = 1.0f;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			modelStack.PushMatrix();
			modelStack.Translate(-30 + i * 10, 0, -30 + j * 10);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(10.f, 10.f, 1.f);
			RenderMesh(meshList[GEO_STONEFLOOR], enableLight);
			modelStack.PopMatrix();
		}
	}

	//Render newspaper
	if (newspaper != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(newspaper->getPosition().convert2glm());
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(1.5f, 1.5f, 1.f);
		meshList[GEO_NEWSPAPER]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
		meshList[GEO_NEWSPAPER]->material.kDiffuse = glm::vec3(1, 1, 1);
		meshList[GEO_NEWSPAPER]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
		meshList[GEO_NEWSPAPER]->material.kShininess = 1.0f;
		RenderMesh(meshList[GEO_NEWSPAPER], enableLight);
		modelStack.PopMatrix();
	}

	meshList[GEO_TREE]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
	meshList[GEO_TREE]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_TREE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_TREE]->material.kShininess = 1.0f;
	for (int i = 0; i < 69; i++) {
		if (trees[i] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(trees[i]->getPosition().convert2glm());
			modelStack.Scale(2.5f, 3.5f, 2.5f);
			RenderMesh(meshList[GEO_TREE], enableLight);
			modelStack.PopMatrix();
		}
	}

	meshList[GEO_FENCE]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
	meshList[GEO_FENCE]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_FENCE]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_FENCE]->material.kShininess = 1.0f;
	modelStack.PushMatrix();
	modelStack.Translate(25.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[GEO_FENCE], enableLight);
	modelStack.PopMatrix();

	meshList[GEO_SIGN]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_SIGN]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_SIGN]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_SIGN]->material.kShininess = 1.0f;
	modelStack.PushMatrix();
	modelStack.Translate(sign->getPosition().convert2glm());
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	RenderMesh(meshList[GEO_SIGN], enableLight);
	modelStack.PopMatrix();

	//Render jars
	meshList[GEO_JAR]->material.kAmbient = glm::vec3(0.1, 0.1, 0.1);
	meshList[GEO_JAR]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_JAR]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_JAR]->material.kShininess = 1.0f;
	for (int i = 0; i < 3; i++) {
		modelStack.PushMatrix();
		modelStack.Translate(jars[i]->getPosition().convert2glm());
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(1.25f, 1.25f, 1.25f);
		RenderMesh(meshList[GEO_JAR], enableLight);
		modelStack.PopMatrix();
	}


	// Render objects
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	//Render balls
	for (int i = 0; i < 5; i++) {
		if (balls[i] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(balls[i]->getPosition().x, balls[i]->getPosition().y, balls[i]->getPosition().z);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_SPHERE], false);
			modelStack.PopMatrix();
		}
	}

	//Player
	if (camera.cameraState != FIRST_PERSON) {
		modelStack.PushMatrix();
		modelStack.Translate(player->getPosition().x, player->getPosition().y, player->getPosition().z);
		modelStack.Scale(player->getHitbox().getHalfDimensions().x * 2, player->getHitbox().getHalfDimensions().y * 2, player->getHitbox().getHalfDimensions().z * 2);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                For Inventory Render                                                //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currGameState == INVENTORY) {
		RenderInventory();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                For Dialogue Render                                                 //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currGameState == DIALOGUE) {
		RenderMeshOnScreen(meshList[GEO_QUAD], 400, 150, 700, 200);
		RenderTextOnScreen(meshList[GEO_TEXT], currInteraction->getCurrDialogue()->text, glm::vec3(1, 1, 1), 0.65f, 16, 100, 175);
	}
}

void SceneBallCup::Exit()
{
	//Game variables cleanup
	for (int i = 0; i < 5; i ++) {
		if (balls[i] != nullptr) {
			delete balls[i];
		}
	}
	for (int i = 0; i < NUM_IOBJS; i++) {
		if (interactableObjs[i] != nullptr) {
			delete interactableObjs[i];
		}
	}
	if (player != nullptr) {
		delete player;
	}
	if (sign != nullptr) {
		delete sign;
	}
	if (newspaper != nullptr) {
		delete newspaper;
	}
	//Sound cleanup
	SoundManager::GetInstance().stopBGM();
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

void SceneBallCup::HandleKeyPress()
{
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
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_I))
	{
		// Load the inventory
		if (currGameState == RUNNING) {
			currGameState = INVENTORY;
		}
		else if (currGameState == INVENTORY) {
			currGameState = RUNNING;
		}
	}

}

void SceneBallCup::RenderSkybox()
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

void SceneBallCup::RenderInventory()
{
	RenderMeshOnScreen(meshList[GEO_QUAD], 400, 300, 700, 400);
	RenderTextOnScreen(meshList[GEO_TEXT], "Inventory", glm::vec3(1, 1, 1), 0.65f, 32, 300, 450);
	if (Inventory::GetInstance().getInventory().size() < 1) {
		RenderTextOnScreen(meshList[GEO_TEXT], "Empty", glm::vec3(1, 1, 1), 0.65f, 16, 300, 350);
	}
	else {
		RenderTextOnScreen(meshList[GEO_TEXT], Inventory::GetInstance().getItem().name, glm::vec3(1, 1, 1), 0.65f, 16, 125, 400);
		if (Inventory::GetInstance().moreThan1Item())
			RenderTextOnScreen(meshList[GEO_TEXT], std::string(" (" + std::to_string(Inventory::GetInstance().getItemQuantity()) + ')'),
				glm::vec3(1, 1, 1), 0.65f, 16, 200, 400);
		RenderTextOnScreen(meshList[GEO_TEXT], Inventory::GetInstance().getItem().description, glm::vec3(1, 1, 1), 0.65f, 16, 100, 350);
		RenderTextOnScreen(meshList[GEO_TEXT], std::string('<' +std::to_string(Inventory::GetInstance().getCurrItemIndex() + 1) +
			'/' + std::to_string(Inventory::GetInstance().getNumUniqueItems()) + '>'), glm::vec3(1, 1, 1), 0.65f, 16, 300, 150);
	}
}

void SceneBallCup::InitLights()
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
	light[0].position = glm::vec3(0, 100, 0);
	light[0].color = glm::vec3(1, 1, 1);
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].power = 0.25f;
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
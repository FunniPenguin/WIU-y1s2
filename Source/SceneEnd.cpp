#include "SceneEnd.h"
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

void SceneEnd::Init()
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

	/// <Note>
	/// Ask Dylan Chan for blood stained ground
	/// <\Note>

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", glm::vec3(1.f, 1.f, 1.f), 1.f, 16, 16);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PLANE] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PLANE]->textureID = LoadTGA("Images//ground.tga");
	meshList[GEO_GRASSFLOOR] = MeshBuilder::GenerateQuad("Grass", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_GRASSFLOOR]->textureID = LoadTGA("Images//Grass.tga");
	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("Plane", glm::vec3(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_TEXTBOX]->textureID = LoadTGA("Images//textBox.tga");

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
	if (Inventory::GetInstance().findItem("salt powder") &&
		Inventory::GetInstance().findItem("exorcism paper") &&
		Inventory::GetInstance().findItem("holy water")) {
		playerWin = true;
	}
	else {
		playerWin = false;
	}
	currGameState = RUNNING;
	player = new Player(Vector3(0, 1, 0));
	// Initialise camera properties
	camera.Init((player->getPosition() + Vector3{ 1.f, 0.f, 0.f }).convert2glm(),
		(player->getPosition() + Vector3{ 2.f, 0.f, 0.f }).convert2glm());
	SoundManager::GetInstance().setBGM(BGM1);
}

void SceneEnd::Update(double dt)
{
	HandleKeyPress();
	if (currGameState == RUNNING) {
		if (KeyboardController::GetInstance()->IsKeyPressed('Q')) {
			SceneManager::GetInstance().LoadScene(SCENE_LOSE);
			return;
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('M')) {
			SoundManager::GetInstance().switchBGM(BGM2);
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('N')) {
			SoundManager::GetInstance().switchBGM(BGM1);
		}
		player->movePlayer(dt, camera);
		//std::cout << player->getPosition().x << "|" << player->getPosition().y << "|" << player->getPosition().z << "|" << std::endl;
		player->UpdatePhysics(dt, camera);
		camera.Update(dt);
		//Update sounds
		SoundManager::GetInstance().updateSounds(dt);
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

void SceneEnd::Render()
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

	//Player
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

	//Render ground
	meshList[GEO_GRASSFLOOR]->material.kAmbient = glm::vec3(0.001, 0.001, 0.001);
	meshList[GEO_GRASSFLOOR]->material.kDiffuse = glm::vec3(1, 1, 1);
	meshList[GEO_GRASSFLOOR]->material.kSpecular = glm::vec3(0.5, 0.5, 0.5);
	meshList[GEO_GRASSFLOOR]->material.kShininess = 1.0f;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			modelStack.PushMatrix();
			modelStack.Translate(-30 + i * 10, 0, -30 + j * 10);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(10.f, 10.f, 1.f);
			RenderMesh(meshList[GEO_GRASSFLOOR], enableLight);
			modelStack.PopMatrix();
		}
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

void SceneEnd::Exit()
{
	if (player != nullptr) {
		delete player;
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

void SceneEnd::HandleKeyPress()
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

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		// Change to black background
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

void SceneEnd::RenderSkybox()
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
void SceneEnd::RenderInventory()
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
		RenderTextOnScreen(meshList[GEO_TEXT], std::string('<' + std::to_string(Inventory::GetInstance().getCurrItemIndex() + 1) +
			'/' + std::to_string(Inventory::GetInstance().getNumUniqueItems()) + '>'), glm::vec3(1, 1, 1), 0.65f, 16, 300, 150);
	}
}
void SceneEnd::InitLights()
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
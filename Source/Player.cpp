#include "Player.h"

#include "KeyboardController.h"
#include "MouseController.h"

//Include GLFW
#include <GLFW/glfw3.h>

void Player::translateObject(Vector3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Player::translateObject(glm::vec3 translation)
{
	translatePosition(translation);
	hitbox.translate(translation);
}

void Player::setObjectPosition(Vector3 Position)
{
	setPosition(Position);
	hitbox.setPosition(Position);
}

void Player::movePlayer(double dt,FPCamera& camera)
{
	Vector3 totalVel{0.f, 0.f, 0.f};
	glm::vec3 view = glm::vec3(camera.view.x, 0, camera.view.z);
	glm::vec3 right = glm::vec3(camera.right.x, 0, camera.right.z);
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_W)) {
		totalVel += (view * camera.cameraMovementSpeed) * static_cast<float>(dt);
		camera.isDirty = true;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_S)) {
		totalVel -= (view * camera.cameraMovementSpeed) * static_cast<float>(dt);
		camera.isDirty = true;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_A)) {
		totalVel -= right * camera.cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		camera.isDirty = true;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_D)) {
		totalVel += right * camera.cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		camera.isDirty = true;
	}
	setVel(getVel() + totalVel);
}

void Player::UpdatePhysics(double dt, FPCamera& camera)
{
	int isRunning = 1;
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		isRunning = 2;
	}
	Vector3 finalAccel = getAccel();
	//if mass is 0, treat object as static/immovable
	if (getMass() > 0)
	{
		//F = MA
		float invMass = 1.f / getMass();
		finalAccel = getAccel() + getTotalForces() * invMass;
	}

	//euler integration
	setVel(getVel().x, 0, getVel().z);
	setVel(getVel() += finalAccel * dt);

	//Player speed limit
	if (getVel().x > 15) {
		setVel(15.f, getVel().y, getVel().z);
	}
	else if (getVel().x < -15) {
		setVel(-15.f, getVel().y, getVel().z);
	}
	if (getVel().y > 15) {
		setVel(getVel().x, 15, getVel().z);
	}
	else if (getVel().y < -15) {
		setVel(getVel().x, -15, getVel().z);
	}
	if (getVel().z > 15) {
		setVel(getVel().x, getVel().y, 15);
	}
	else if (getVel().z < -15) {
		setVel(getVel().x, getVel().y, -15);
	}

	translateObject(getVel() * dt);
	camera.target += (getVel() * dt).convert2glm();
	camera.position += (getVel() * dt).convert2glm();

	//clear forces
	getTotalForces().SetZero();

	//do angular movement
	addRotation(getAngularVel() * dt);

	setVel(getVel() * pow(0.5f, dt)); //linear drag
}

BoxCollider& Player::getHitbox()
{
	return hitbox;
}

Player::Player(Vector3 Position) : PhysicsObject(Position, 0.f), hitbox(Position, 0.5f, 1.f, 0.5f)
{
	setBounciness(1.f);
}

Player::~Player()
{
}

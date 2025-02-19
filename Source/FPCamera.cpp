#include "FPCamera.h"
#include "KeyboardController.h"
#include "MouseController.h"

//Include GLFW
#include <GLFW/glfw3.h>

FPCamera::FPCamera() : isDirty(false)
{
	this->position = glm::vec3(0, 0, 0);
	this->target = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0, 1, 0);
	cameraState = FIRST_PERSON;
}

FPCamera::~FPCamera()
{
}



void FPCamera::Init(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->isDirty = false; //set to true if want the view to rotate like an aeroplane

	Refresh();
}

void FPCamera::Reset()
{
}

void FPCamera::Update(double dt)
{
	float originalY = position.y;
	float rotateSpeed = 100.f;
	float cameraMovementSpeed = 10.f;
	glm::vec3 view = glm::normalize(target - position);
	glm::vec3 right = glm::normalize(glm::cross(view, up));
	//Rotate by mouse
	double deltaX = MouseController::GetInstance()->GetMouseDeltaX();
	xRot = -deltaX * rotateSpeed * 0.5f * static_cast<float>(dt);
	glm::mat4 yaw = glm::rotate(glm::mat4(1.f),// matrix to modify
		glm::radians(xRot),// rotation angle in degree and	converted to radians
		glm::vec3(up.x, up.y, up.z)// the axis to rotate along
	);
	glm::vec3 yawView = yaw * glm::vec4(view, 0.f);
	//add keyboard rotation
	float deltaY = MouseController::GetInstance()->GetMouseDeltaY();
	yRot = deltaY * rotateSpeed * 0.5f * static_cast<float>(dt);
	yRot = glm::clamp(yRot, -80.f, 80.f);
	right.y = 0;
	glm::mat4 yaw2 = glm::rotate(glm::mat4(1.f),// matrix to modify
		glm::radians(yRot),// rotation angle in degree and	converted to radians
		glm::vec3(right.x, right.y, right.z)// the axis to rotate along
	);
	glm::vec3 yawView2 = yaw2 * glm::vec4(view, 0.f);
	target = position + glm::normalize(yawView + yawView2);
	isDirty = false;

	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_UP)) {
		right.y = 0; // Right vector should not point any y direction
		// Calculate amount of angle to rotate
		float angle = rotateSpeed * static_cast<float>(dt);
		glm::mat4 pitch = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(right.x, right.y, right.z)); // Rotate on right vector
		// Calculate the rotated view vector
		glm::vec3 rotatedView = pitch * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_DOWN)) {
		right.y = 0; // Right vector should not point any y direction
		// Calculate amount of angle to rotate
		float angle = rotateSpeed * static_cast<float>(dt);
		glm::mat4 pitch = glm::rotate(glm::mat4(1.f), glm::radians(-angle), glm::vec3(right.x, right.y, right.z)); // Rotate on right vector
		// Calculate the rotated view vector
		glm::vec3 rotatedView = pitch * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_W)) {
		position.x += (view * cameraMovementSpeed).x * static_cast<float>(dt);
		position.z += (view * cameraMovementSpeed).z * static_cast<float>(dt);
		target.x += (view * cameraMovementSpeed).x * static_cast<float>(dt);
		target.z += (view * cameraMovementSpeed).z * static_cast<float>(dt);
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_S)) {
		// To do for opposite direction
		position.x -= (view * cameraMovementSpeed).x * static_cast<float>(dt);
		position.z -= (view * cameraMovementSpeed).z * static_cast<float>(dt);
		target.x -= (view * cameraMovementSpeed).x * static_cast<float>(dt);
		target.z -= (view * cameraMovementSpeed).z * static_cast<float>(dt);
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_D)) {
		position += right * cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		target += right * cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_A)) {
		position -= right * cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		target -= right * cameraMovementSpeed * static_cast<float>(dt); // Use right vector
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT)) {
		// Calculate amount of angle to rotate
		float angle = rotateSpeed * static_cast<float>(dt);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.f), // Default identity
			glm::radians(angle), // Convert degree angle to radians
			glm::vec3(up.x, up.y, up.z) // Use camera Up vector to rotate
		);
		// Calculate the rotated view vector
		glm::vec3 rotatedView = yaw * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_RIGHT)) {
		float angle = rotateSpeed * static_cast<float>(dt);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.f), // Default identity
			glm::radians(-angle), // Convert degree angle to radians
			glm::vec3(up.x, up.y, up.z) // Use camera Up vector to rotate
		);
		// Calculate the rotated view vector
		glm::vec3 rotatedView = yaw * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = false; //set to true if want the view to rotate like an aeroplane
	}
}

void FPCamera::Refresh()
{
	if (!this->isDirty) return;
	glm::vec3 view = glm::normalize(target - position);
	glm::vec3 right = glm::normalize(glm::cross(up, view));
	// Recalculate the up vector
	this->up = glm::normalize(glm::cross(view, right));
	this->isDirty = false;
}
#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"
#include "PhysicsObject.h"
#include "BoxCollider.h"
//To allign player movement with camera
#include "FPCamera.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class Player : public PhysicsObject
{
private:
	BoxCollider hitbox;
public:
	//Note: Overload a game object's set and translate functions if the object has a hitbox so that the hibox gets moved
	void translateObject(Vector3 translation);
	void translateObject(glm::vec3 translation);
	void setObjectPosition(Vector3 Position);
	void movePlayer(double dt, FPCamera& camera);
	void UpdatePhysics(double dt, FPCamera& camera);

	BoxCollider& getHitbox();

	Player(Vector3 Position);
	~Player();
};

#endif
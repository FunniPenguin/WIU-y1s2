#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

//Vector class is from FORMOP, only extra thing added was conversion from Vector3 to glm::vec3 and contructor with glm::vec3
#include "Vector3.h"

//Enum class to simplify changing just 1 of the 3 positions
enum AXIS {
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};
class GameObject
{
private:
	Vector3 position;
	Vector3 rotation;
public:
	Vector3 getPosition() const;
	void setPosition(Vector3 Position);
	void setPosition(AXIS axis, int value);
	void translatePosition(Vector3 Position);
	void translatePosition(AXIS axis, int value);
	virtual void translateObject(Vector3 Position);
	virtual void translateObject(glm::vec3 Position);
	virtual void setObjectPosition(Vector3 Position);
	Vector3 getRotation() const;
	void setRotation(Vector3 Rotation);
	void setRotation(AXIS axis, int value);
	void addRotation(Vector3 Rotation);
	void addRotation(AXIS axis, int value);

	GameObject();
	GameObject(float x, float y, float z);
	GameObject(float x, float y, float z, Vector3 rotation);
	GameObject(Vector3 Position);
	GameObject(glm::vec3 Position);
	~GameObject() {};
};

#endif
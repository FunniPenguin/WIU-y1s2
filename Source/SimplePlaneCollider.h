#ifndef PLANE_COLLIRDER_H
#define PLANE_COLLIRDER_H

#include "Vector3.h"
#include "BaseCollider.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

class SimplePlaneCollider : public BaseCollider
{
private:
	Vector3* min; 
	Vector3* max;
	Vector3 vertice1Translation, vertice2Translation;
	Vector3 vertices[4];
public:
	void setPosition(Vector3 Origin);
	void setPosition(glm::vec3 Origin);
	void translate(Vector3 translation);
	void translate(glm::vec3 translation);
	Vector3& getMin();
	Vector3& getMax();

	//Note: vertice translations are to translate 2 vertices from the origin, vertices are bottom left and top right
	//Note: This is a simple plane collider so the y translation is assumed to be 0
	SimplePlaneCollider( Vector3 Origin,Vector3 Vertice1Translation, Vector3 Vertice2Translation);
	~SimplePlaneCollider();
};

#endif
#include "SimplePlaneCollider.h"

void SimplePlaneCollider::setPosition(Vector3 Origin)
{
	vertices[0] = Origin + vertice1Translation;
	vertices[3] = Origin + vertice2Translation;
	vertices[1] = Origin + Vector3(vertice1Translation.x, 0, vertice2Translation.z);
	vertices[2] = Origin + Vector3(vertice2Translation.x, 0, vertice1Translation.z);
}

void SimplePlaneCollider::setPosition(glm::vec3 Origin)
{
	vertices[0] = Origin + vertice1Translation.convert2glm();
	vertices[3] = Origin + vertice2Translation.convert2glm();
	vertices[1] = Origin + Vector3(vertice1Translation.x, 0, vertice2Translation.z).convert2glm();
	vertices[2] = Origin + Vector3(vertice2Translation.x, 0, vertice1Translation.z).convert2glm();
}

void SimplePlaneCollider::translate(Vector3 translation)
{
	vertices[0] += translation;
	vertices[3] += translation;
	vertices[1] += translation;
	vertices[2] += translation;
}

void SimplePlaneCollider::translate(glm::vec3 translation)
{
	vertices[0] += translation;
	vertices[3] += translation;
	vertices[1] += translation;
	vertices[2] += translation;
}

Vector3& SimplePlaneCollider::getMin()
{
	return *min;
}

Vector3& SimplePlaneCollider::getMax()
{
	return *max;
}

SimplePlaneCollider::SimplePlaneCollider(Vector3 Origin, Vector3 Vertice1Translation, Vector3 Vertice2Translation)
{
	vertice1Translation = Vector3(Vertice1Translation.x, 0, Vertice1Translation.z);
	vertice2Translation = Vector3(Vertice2Translation.x, 0, Vertice2Translation.z);
	vertices[0] = Origin + vertice1Translation;
	vertices[3] = Origin + vertice2Translation;
	vertices[1] = Origin + Vector3(vertice1Translation.x, 0, vertice2Translation.z);
	vertices[2] = Origin + Vector3(vertice2Translation.x, 0, vertice1Translation.z);
	min = &vertices[0];
	max = &vertices[0];
	for (int i = 1; i < 4; i++) {
		if ((min->x >= vertices[i].x) && (min->z >= vertices[i].z)) {
			min = &vertices[i];
		}
		if ((max->x <= vertices[i].x) && (max->z <= vertices[i].z)) {
			max = &vertices[i];
		}
	}
}

SimplePlaneCollider::~SimplePlaneCollider()
{
}

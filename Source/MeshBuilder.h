#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateSphere(const std::string& meshName, glm::vec3 color, float radius = 1.f, int numSlice = 360, int numStack = 360);
	static Mesh* GenerateRing(const std::string& meshName, glm::vec3 color, unsigned numSlice, float innerR, float outerR);
	static Mesh* GenerateCube(const std::string& meshName, glm::vec3 color, float length);
	static Mesh* GenerateHemisphere(const std::string& meshName, glm::vec3 color, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateCylinder(const std::string& meshName, glm::vec3 color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateTorus(const std::string & meshName, glm::vec3 color, float innerR = 1.f, float outerR = 1.f, int numSlice = 360, int numStack = 360);
	static Mesh* GenerateHollowCylinder(const std::string& meshName, glm::vec3 color, unsigned numSlice, float radius1, float radius2, float height);
	static Mesh* GenerateQuad(const std::string& meshName, glm::vec3 color, float length);
	static Mesh* GenerateOBJ(const std::string& meshName, const	std::string& file_path);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
};

#endif
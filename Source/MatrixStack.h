#ifndef MatrixStack_H
#define MatrixStack_H

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <stack>

class MatrixStack
{
public:
MatrixStack();
~MatrixStack();
const glm::mat4& Top() const;
void PopMatrix();
void PushMatrix();
void Clear();
void LoadIdentity();
void LoadMatrix(const glm::mat4& matrix);
void MultMatrix(const glm::mat4& matrix);
void Rotate(float degrees, float axisX, float axisY, float axisZ);
void Scale(float scaleX, float scaleY, float scaleZ);
void Translate(float translateX, float translateY, float translateZ);
void Translate(const glm::vec3 translation); //Done by DylanYap
void Scale(const glm::vec3 scale); //Done by DylanYap
void Frustum(double left, double right, double bottom, double top, double near, double
far);
void LookAt(double eyeX, double eyeY, double eyeZ,
double centerX, double centerY, double centerZ,
double upX, double upY, double upZ);
private:
std::stack<glm::mat4> ms;
};

#endif
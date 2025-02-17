#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <iostream>

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

struct Vector3
{
	float x, y, z;

	explicit Vector3(float a = 0.0, float b = 0.0, float c = 0.0);
	Vector3(const Vector3& rhs);
	Vector3(glm::vec3 anotherVec); //Done by Dylan Yap
	~Vector3();

	void Set(float a = 0, float b = 0, float c = 0); //Set all data
	void SetZero(void); //Set all data to zero

	Vector3 operator+(const Vector3& rhs) const; //Vector addition
	Vector3& operator+=(const Vector3& rhs);

	Vector3 operator-(const Vector3& rhs) const; //Vector subtraction
	Vector3& operator-=(const Vector3& rhs);

	Vector3 operator-(void) const; //Unary negation

	Vector3 operator*(float scalar) const; //Scalar multiplication
	Vector3& operator*=(float scalar);

	bool operator==(const Vector3& rhs) const; //Equality check
	bool operator!= (const Vector3& rhs) const; //Inequality check

	Vector3& operator=(const Vector3& rhs); //Assignment operator

	float Length(void) const; //Get magnitude
	float LengthSquared(void) const; //Get square of magnitude
	float Distance(const Vector3& rhs) const; //Get the distance 
	float DistanceSquared(const Vector3& rhs) const; //Get the distance squared 
	static float Distance(const Vector3& lhs, const Vector3& rhs);
	static float DistanceSquared(const Vector3& lhs, const Vector3& rhs);

	float Dot(const Vector3& rhs) const; //Dot product
	Vector3 Cross(const Vector3& rhs) const; //Cross product

	//Return a copy of this vector, normalized
	Vector3 Normalized(void) const;

	//Normalize this vector and return a reference to it
	Vector3& Normalize(void);

	//Rotate a Vector
	static Vector3 RotateVector(const Vector3& v, float rad);

	//Convert this vector to glm::vec3
	glm::vec3 convert2glm(); //Done by Dylan Yap
};
Vector3 operator*(float scalar, const Vector3& rhs);

#endif
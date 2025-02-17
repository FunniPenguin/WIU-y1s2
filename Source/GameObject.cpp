#include "GameObject.h"

Vector3 GameObject::getPosition() const
{
    return position;
}

void GameObject::setPosition(Vector3 Position)
{
    position = Position;
}

void GameObject::setPosition(AXIS axis, int value)
{
    if (axis == X_AXIS) {
        position.x = value;
    }
    else if (axis == Y_AXIS) {
        position.y = value;
    }
    else if (axis == Z_AXIS) {
        position.z = value;
    }
}

void GameObject::translatePosition(Vector3 Position)
{
    position += Position;
}

void GameObject::translatePosition(AXIS axis, int value)
{
    if (axis == X_AXIS) {
        position.x += value;
    }
    else if (axis == Y_AXIS) {
        position.y += value;
    }
    else if (axis == Z_AXIS) {
        position.z += value;
    }
}

Vector3 GameObject::getRotation() const
{
    return rotation;
}

void GameObject::setRotation(Vector3 Rotation)
{
    rotation = Rotation;
}

void GameObject::setRotation(AXIS axis, int value)
{
    if (axis == X_AXIS) {
        rotation.x = value;
    }
    else if (axis == Y_AXIS) {
        rotation.y = value;
    }
    else if (axis == Z_AXIS) {
        rotation.z = value;
    }
}

void GameObject::addRotation(Vector3 Rotation)
{
    rotation += Rotation;
}

void GameObject::addRotation(AXIS axis, int value)
{
    if (axis == X_AXIS) {
        rotation.x += value;
    }
    else if (axis == Y_AXIS) {
        rotation.y += value;
    }
    else if (axis == Z_AXIS) {
        rotation.z += value;
    }
}

GameObject::GameObject() : position{}, rotation{ 0 }
{
}

GameObject::GameObject(float x, float y, float z) : position{x,y,z}, rotation{ 0, 0, 0 }
{
}

GameObject::GameObject(float x, float y, float z, Vector3 Rotation) : position{x,y,z}, rotation{ Rotation.x, Rotation.y, Rotation.z }
{
}

GameObject::GameObject(Vector3 Position) : position{Position.x, Position.y, Position.z}, rotation{ 0, 0, 0 }
{
}

GameObject::GameObject(glm::vec3 Position) : position{ Position.x, Position.y, Position.z }, rotation{ 0, 0, 0 }
{
}

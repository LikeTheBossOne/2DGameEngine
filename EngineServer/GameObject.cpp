#include "GameObject.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "RectangleColliderComponent.h"
#include "PlayerInputComponent.h"
#include "TextureComponent.h"

int GameObject::nextId = 0;

GameObject::GameObject()
{
	_GUID = nextId;
	nextId++;
}


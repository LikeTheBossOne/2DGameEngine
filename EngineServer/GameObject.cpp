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

	_transform = nullptr;
	_rigidBody = nullptr;
}

GameObject::GameObject(const GameObject& other)
{
	_GUID = other._GUID;
	
	_transform = nullptr;
	_rigidBody = nullptr;

	_components = std::unordered_map<ComponentTypes, GenericComponent*>();
}

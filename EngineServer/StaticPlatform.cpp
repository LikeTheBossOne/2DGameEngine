#include "StaticPlatform.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "RectangleColliderComponent.h"
#include "PhysicsEngineSettings.h"
#include "ColorComponent.h"

StaticPlatform::StaticPlatform(PhysicsEngineSettings* physSettings, Rect position, int r, int g, int b)
{
	_transform = new TransformComponent(this, position, true);
	
	_rigidBody = new RigidBodyComponent(this, physSettings, true, false, false, true, false, false, true);
	
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		this, 0, 0, position.getWidth(), position.getHeight());
	
	_components[ComponentTypes::ColorComponent] = new ColorComponent(this, r, g, b);
}

StaticPlatform::StaticPlatform(const StaticPlatform& other, PhysicsEngineSettings* physSettings) : GameObject(other)
{
	_transform = new TransformComponent(*other._transform, this);
	_rigidBody = new RigidBodyComponent(*other._rigidBody, this, physSettings);
	
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		*static_cast<RectangleColliderComponent*>(other._components.at(ComponentTypes::RectangleColliderComponent)), this
	);

	_components[ComponentTypes::ColorComponent] = new ColorComponent(
		*static_cast<ColorComponent*>(other._components.at(ComponentTypes::ColorComponent)), this
	);
}

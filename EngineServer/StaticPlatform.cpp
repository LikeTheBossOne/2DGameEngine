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

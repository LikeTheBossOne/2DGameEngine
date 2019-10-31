#include "PatternPlatform.h"
#include <utility>
#include "Pattern.h"
#include "TransformComponent.h"
#include "RectangleColliderComponent.h"
#include "RigidBodyComponent.h"
#include "PatternComponent.h"
#include "ColorComponent.h"
#include "MovementComponent.h"

PatternPlatform::PatternPlatform(PhysicsEngineSettings* physSettings, Rect position, int r, int g, int b,
	std::vector<Pattern*> patterns)
{
	_transform = new TransformComponent(this, position, true);

	_rigidBody = new RigidBodyComponent(this, physSettings, false, false, false, true, false, false, true);

	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		this, 0, 0, position.getWidth(), position.getHeight());

	_components[ComponentTypes::ColorComponent] = new ColorComponent(this, r, g, b);

	_components[ComponentTypes::MovementComponent] = new MovementComponent(this);

	_components[ComponentTypes::PatternComponent] = new PatternComponent(this, std::move(patterns));
}

#include "Player.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "RectangleColliderComponent.h"
#include "PlayerInputComponent.h"
#include "JumpComponent.h"
#include "MovementComponent.h"
#include "PhysicsEngineSettings.h"
#include "TextureComponent.h"

Player::Player(PhysicsEngineSettings* physSettings, Rect position, std::string textureName)
{
	_transform = new TransformComponent(this, position);

	_rigidBody = new RigidBodyComponent(this, physSettings, false, true, false, true, true, false);


	// Initialize Collider
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		this, 0, 0, position.getWidth(), position.getHeight());

	// Initialize Movement
	_components[ComponentTypes::MovementComponent] = new MovementComponent(this);

	// Initialize PlayerInput
	_components[ComponentTypes::PlayerInputComponent] = new PlayerInputComponent(this, -1, 1);

	// Initialize Jump
	_components[ComponentTypes::JumpComponent] = new JumpComponent(this, 2);

	// Initialize Texture
	_components[ComponentTypes::TextureComponent] = new TextureComponent(this, textureName);
}

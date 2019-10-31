#include "Player.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "RectangleColliderComponent.h"
#include "PlayerInputComponent.h"
#include "JumpComponent.h"
#include "MovementComponent.h"
#include "PhysicsEngineSettings.h"
#include "TextureComponent.h"
#include "DieComponent.h"
#include "SpawnZone.h"

Player::Player(PhysicsEngineSettings* physSettings, float width, float height, std::string textureName, SpawnZone* spawn)
{
	_transform = new TransformComponent(this,
		Rect(spawn->getTransform()->getPositionX(), spawn->getTransform()->getPositionX(), width, height), true);

	_rigidBody = new RigidBodyComponent(this, physSettings, false, false, true, false, true, true, false);


	// Initialize Collider
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		this, 0, 0, width, height);

	// Initialize Movement
	_components[ComponentTypes::MovementComponent] = new MovementComponent(this);

	// Initialize PlayerInput
	_components[ComponentTypes::PlayerInputComponent] = new PlayerInputComponent(this, -1, 1);

	// Initialize Jump
	_components[ComponentTypes::JumpComponent] = new JumpComponent(this, 2);

	// Initialize Texture
	_components[ComponentTypes::TextureComponent] = new TextureComponent(this, textureName);

	// Initialize Die Component
	_components[ComponentTypes::DieComponent] = new DieComponent(this, true, spawn);
}

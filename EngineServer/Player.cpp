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
#include "SpawnableComponent.h"

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
	_components[ComponentTypes::DieComponent] = new DieComponent(this, true);

	// Initialize Spawnable Component
	_components[ComponentTypes::SpawnableComponent] = new SpawnableComponent(this, spawn);
}

Player::Player(const Player& other, PhysicsEngineSettings* physSettings, SpawnZone* spawn) : GameObject(other)
{
	_transform = new TransformComponent(*other._transform, this);

	_rigidBody = new RigidBodyComponent(*other._rigidBody, this, physSettings);
	
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		*static_cast<RectangleColliderComponent*>(other._components.at(ComponentTypes::RectangleColliderComponent)), this
	);

	_components[ComponentTypes::MovementComponent] = new MovementComponent(
		*static_cast<MovementComponent*>(other._components.at(ComponentTypes::MovementComponent)), this
	);

	_components[ComponentTypes::PlayerInputComponent] = new PlayerInputComponent(
		*static_cast<PlayerInputComponent*>(other._components.at(ComponentTypes::PlayerInputComponent)), this
	);

	_components[ComponentTypes::JumpComponent] = new JumpComponent(
		*static_cast<JumpComponent*>(other._components.at(ComponentTypes::JumpComponent)), this
	);

	_components[ComponentTypes::TextureComponent] = new TextureComponent(
		*static_cast<TextureComponent*>(other._components.at(ComponentTypes::TextureComponent)), this
	);

	_components[ComponentTypes::DieComponent] = new DieComponent(
		*static_cast<DieComponent*>(other._components.at(ComponentTypes::DieComponent)), this
	);

	_components[ComponentTypes::SpawnableComponent] = new SpawnableComponent(
		*static_cast<SpawnableComponent*>(other._components.at(ComponentTypes::SpawnableComponent)), this, spawn
	);
}

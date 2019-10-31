#pragma once
#include "GenericComponent.h"

class GameObject;
class PhysicsEngineSettings;

class RigidBodyComponent : public GenericComponent
{
public:
	RigidBodyComponent(GameObject* gameObject, PhysicsEngineSettings* physicsEngineSettings);
	RigidBodyComponent(GameObject* gameObject, PhysicsEngineSettings* physicsEngineSettings, bool isStatic, bool ignoreCollisions,
	                   bool useGravity, bool isSticky, bool canStickToSurface, bool isPushable, bool canPush);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::RigidBodyComponent; };

	void setIsStatic(bool isStatic) { _isStatic = isStatic; }
	void setIgnoreCollisions(bool ignoreCollisions) { _ignoreCollisions = ignoreCollisions; }
	void setUseGravity(bool useGravity) { _useGravity = useGravity; }
	void setIsStickySurface(bool isStickySurface) { _isStickySurface = isStickySurface; }
	void setCanStickToSurface(bool canStickToSurface) { _canStickToSurface = canStickToSurface; }
	void setIsPushable(bool isPushable) { _isPushable = isPushable; }
	void setCanPush(bool canPush) { _canPush = canPush; }
	void setStuckToEntity(GameObject* stuckToEntity) { _stuckToEntity = stuckToEntity; }

	PhysicsEngineSettings* getPhysicsEngineSettings() { return _physicsEngineSettings; }
	bool isStatic() { return _isStatic; }
	bool getIgnoreCollisions() { return _ignoreCollisions; }
	bool getUseGravity() { return _useGravity; }
	bool isStickySurface() { return _isStickySurface; }
	bool getCanStickToSurface() { return _canStickToSurface; }
	bool isPushable() { return _isPushable; }
	bool getCanPush() { return _canPush; }
	GameObject* getStuckToEntity(GameObject* stuckToEntity) { return _stuckToEntity; }

private:
	PhysicsEngineSettings* _physicsEngineSettings;
	
	bool _isStatic;
	bool _ignoreCollisions;
	
	bool _useGravity;
	bool _isStickySurface;
	bool _canStickToSurface;
	bool _isPushable;
	bool _canPush;

	GameObject* _stuckToEntity;
};

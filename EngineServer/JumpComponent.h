#pragma once
#include "GenericComponent.h"

class JumpComponent : public GenericComponent
{
public:
	static bool scriptInitialized;
	
	JumpComponent(GameObject* gameObject, float jumpAcceleration);
	JumpComponent(const JumpComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::JumpComponent; };

	void setJumpAcceleration(float jumpAcceleration) { _jumpAcceleration = jumpAcceleration; }
	void setIsJumping(bool isJumping) { _isJumping = isJumping; }
	void setShouldJump(bool shouldJump) { _shouldJump = shouldJump; }

	float getJumpAcceleration() { return _jumpAcceleration; }
	bool isJumping() { return _isJumping; }
	bool shouldJump() { return _shouldJump; }
private:
	float _jumpAcceleration;
	bool _isJumping;
	bool _shouldJump;
};

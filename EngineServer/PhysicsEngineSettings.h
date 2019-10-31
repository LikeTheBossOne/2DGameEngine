#pragma once
class PhysicsEngineSettings
{
public:
	PhysicsEngineSettings() = default;

	void setGravityX(float gravityX) { _gravityX = gravityX; }
	void setGravityY(float gravityY) { _gravityY = gravityY; }
	void setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; }
	
	float getGravityX() { return _gravityX; }
	float getGravityY() { return _gravityY; }
	float getMaxSpeed() { return _maxSpeed; }

private:
	float _gravityX;
	float _gravityY;
	float _maxSpeed;
};


#pragma once

class TransformComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();
private:
	TransformComponent* _positionComponent;
	
};


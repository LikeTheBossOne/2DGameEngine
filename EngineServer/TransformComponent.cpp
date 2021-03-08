#include "TransformComponent.h"
#include "MovementComponent.h"
#include "duktape.h"
#include "ScriptManager.h"
#include <dukglue/dukglue.h>
#include "TransformComponentParameter.h"

bool TransformComponent::scriptInitialized = false;

TransformComponent::TransformComponent(GameObject* gameObject, Rect position, bool isVisible) : GenericComponent(gameObject)
{
	if (!scriptInitialized)
	{
		ScriptManager::getInstance()->registerScript("TransformComponent.update", "scripts/TransformComponent.js", "update");

		duk_context* ctx = ScriptManager::getInstance()->getContext();
		dukglue_register_property(ctx, &TransformComponent::getPositionX, &TransformComponent::setPositionX, "positionX");
		dukglue_register_property(ctx, &TransformComponent::getPositionY, &TransformComponent::setPositionY, "positionY");
		dukglue_register_property(ctx, &TransformComponent::getWidth, &TransformComponent::setWidth, "width");
		dukglue_register_property(ctx, &TransformComponent::getHeight, &TransformComponent::setHeight, "height");
		dukglue_register_property(ctx, &TransformComponent::isVisible, &TransformComponent::setIsVisible, "isVisible");
		dukglue_register_property(ctx, &TransformComponent::getPrevX, &TransformComponent::setPrevX, "prevX");
		dukglue_register_property(ctx, &TransformComponent::getPrevY, &TransformComponent::setPrevY, "prevY");
		scriptInitialized = true;
	}
	
	_position = position;

	_isVisible = isVisible;
	
	_prevX = position.getX();
	_prevY = position.getY();
}

/**
 * Copy Constructor
 */
TransformComponent::TransformComponent(const TransformComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_position = other._position;
	_isVisible = other._isVisible;
	_prevX = other._prevX;
	_prevY = other._prevY;
}

void TransformComponent::update(int deltaTime)
{
	TransformComponentParameter param(this);
	std::vector<Parameter*> sParams;
	sParams.emplace_back(&param);

	ScriptReturnValue retVal(ParameterType::NONE);

	ScriptManager::getInstance()->run("TransformComponent.update", sParams, &retVal);
}

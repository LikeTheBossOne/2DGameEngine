#include "KillComponent.h"

KillComponent::KillComponent(GameObject* gameObject) : GenericComponent(gameObject)
{
}

KillComponent::KillComponent(const KillComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	
}

void KillComponent::update(int deltaTime)
{
}

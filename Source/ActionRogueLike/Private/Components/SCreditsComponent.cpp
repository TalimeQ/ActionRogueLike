

#include "Components/SCreditsComponent.h"

// Sets default values for this component's properties
USCreditsComponent::USCreditsComponent() : Super()
{
	
}

int32 USCreditsComponent::GetCreditsAmount() const
{
	return CreditsAmount;
}

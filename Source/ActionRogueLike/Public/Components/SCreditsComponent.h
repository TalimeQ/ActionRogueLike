#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCreditsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USCreditsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USCreditsComponent();

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCreditsAmount() const;
	
protected:
	// Negative or positive being either credit costs or gains
	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsAmount = 0;
		
};

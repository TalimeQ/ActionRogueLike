// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Effects/SActionEffect.h"
#include "SThornsEffect.generated.h"

class USAttributesComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USThornsEffect : public USActionEffect
{
	GENERATED_BODY()

public:
	USThornsEffect();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void ReflectDamage(AActor* InstigatorActor,USAttributesComponent* OwningComp,float NewHealth,float Delta);
	
	virtual void ExecutePeriodicEffect_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta = (ClampMax = 1.0f, ClampMin = 0.0f,UIMax = 1.0f, UIMin = 0.0f))
	float PercentReflected = 0.5f;
};

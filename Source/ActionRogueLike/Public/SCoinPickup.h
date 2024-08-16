// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractableActor.h"
#include "SCoinPickup.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPickup : public ASInteractableActor
{
	GENERATED_BODY()

public:
	ASCoinPickup();
	
protected:
	virtual void TriggerPayload_Implementation(APawn* InstigatorPawn) override;

	virtual void ShowActor_Implementation() override;

	virtual void HideActor_Implementation() override;

	virtual bool CanTriggerInteraction_Implementation(APawn* InstigatorPawn) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HealthPotion")
	float HealthRestored = 50.0f;

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	USphereComponent* SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	UStaticMeshComponent* CoinMesh= nullptr;
};

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

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	TObjectPtr<USphereComponent> SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	TObjectPtr<UStaticMeshComponent> CoinMesh= nullptr;

	UPROPERTY(EditAnywhere,  Category = "Components")
	int32 CoinsRewarded = 20;
};

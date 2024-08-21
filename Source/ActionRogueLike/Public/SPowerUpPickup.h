// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractableActor.h"
#include "SPowerUpPickup.generated.h"

class USphereComponent;
class USAction;

UCLASS()
class ACTIONROGUELIKE_API ASPowerUpPickup : public ASInteractableActor
{
	GENERATED_BODY()
public:
	ASPowerUpPickup();
	
protected:
	virtual void TriggerPayload_Implementation(APawn* InstigatorPawn) override;

	virtual void ShowActor_Implementation() override;

	virtual void HideActor_Implementation() override;

	virtual bool CanTriggerInteraction_Implementation(APawn* InstigatorPawn) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Power Up")
	TSubclassOf<USAction> GrantedAction;

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	TObjectPtr<USphereComponent> SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,  Category = "Components")
	TObjectPtr<UStaticMeshComponent> PowerupMesh = nullptr;
};

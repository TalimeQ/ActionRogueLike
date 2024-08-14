// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractableActor.h"
#include "SHealthPotion.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASInteractableActor
{
	GENERATED_BODY()
	
public:
	ASHealthPotion();
	
protected:
	virtual void TriggerPayload_Implementation(APawn* InstigatorPawn) override;

	virtual void ShowActor_Implementation() override;

	virtual void HideActor_Implementation() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HealthPotion")
	float HealthRestored = 50.0f;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PotionMesh = nullptr;
};

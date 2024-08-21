// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SInteractableActor.generated.h"

class USCreditsComponent;

UCLASS()
class ACTIONROGUELIKE_API ASInteractableActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASInteractableActor();

	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void TriggerInteraction(APawn* InstigatorPawn);

	UFUNCTION()
	void OnReactivationFinished();
	
	UFUNCTION(BlueprintNativeEvent)
	void HideActor();

	UFUNCTION(BlueprintNativeEvent)
	void ShowActor();

	UFUNCTION(BlueprintNativeEvent)
	void TriggerPayload(APawn* InstigatorPawn);

	UFUNCTION(BlueprintNativeEvent)
	bool CanTriggerInteraction(APawn* InstigatorPawn);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Interactable")
	bool bReactivates = true;

	UPROPERTY(EditDefaultsOnly, Category = "Interactable")
	float TimeToReactivate = 10.0f;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsActive = true;

	FTimerHandle ResetTimerHandle;
};

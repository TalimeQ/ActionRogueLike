// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/AttributesInterface.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributesComponent;
class UUserWidget;
class USWorldUserWidget;
class USCreditsComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter , public IAttributesInterface
{
	GENERATED_BODY()

public:
	ASAICharacter();
	
	virtual void PostInitializeComponents() override;
	
	USAttributesComponent* GetAttributesComp() const;
	
	bool IsAlive();

protected:
	UFUNCTION()
	void OnPawnSensed(APawn* Pawn);

	UFUNCTION()
	virtual USAttributesComponent* GetAttributesComponent_Implementation() override;
	void TriggerHitFlash();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* NewTarget);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Componnets")
	USAttributesComponent* AttributesComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USCreditsComponent* CreditsComponent = nullptr;

	UPROPERTY(EditDefaultsOnly,  Category = "Visual")
	FName ColorParam;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName HitParam;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FColor HitFlashColor;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY()
	USWorldUserWidget* ActiveHealthBar = nullptr;
};

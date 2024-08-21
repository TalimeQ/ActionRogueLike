// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/AttributesInterface.h"
#include "Interfaces/SCreditsInterface.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributesComponent;
class UUserWidget;
class USWorldUserWidget;
class USActionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter , public IAttributesInterface , public ISCreditsInterface
{
	GENERATED_BODY()

public:
	ASAICharacter();
	
	virtual void PostInitializeComponents() override;
	
	USAttributesComponent* GetAttributesComp() const;

	virtual int32 GetCreditsReward_Implementation() const override {return CreditsAwarded;};
	
	bool IsAlive();

protected:
	UFUNCTION()
	void OnPawnSensed(APawn* Pawn);

	UFUNCTION()
	virtual USAttributesComponent* GetAttributesComponent_Implementation() const override;
	
	void TriggerHitFlash();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* NewTarget);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componnets")
	USAttributesComponent* AttributesComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldUserWidget> SpottedWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	int32 CreditsAwarded = 10;

	UPROPERTY()
	TObjectPtr<USWorldUserWidget> SpottedWidgetInstance;

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

private:
	TWeakObjectPtr<AActor> CachedTarget;
};

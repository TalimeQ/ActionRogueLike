// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/SAction.h"
#include "SActionProjectileAttack.generated.h"


class UAnimMontage;
class UParticleSystem;


UCLASS()
class ACTIONROGUELIKE_API USActionProjectileAttack : public USAction
{
	GENERATED_BODY()

public:

	USActionProjectileAttack();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void AttackDelayElapsed(ACharacter* InstigatorCharacter);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TObjectPtr<UAnimMontage> AttackAnimMontage = nullptr;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TObjectPtr<UParticleSystem> CastingEmitterTemplate = nullptr;

	UPROPERTY(EditAnywhere,Category = "Attack")
	FName HandSocketName;

	UPROPERTY(EditAnywhere,Category = "Attack")
	float AttackAnimDelay;
};

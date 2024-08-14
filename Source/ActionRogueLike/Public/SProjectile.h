// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASProjectile();

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComponent = nullptr;
};

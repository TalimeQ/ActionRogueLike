// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASProjectile();

	virtual void PostInitializeComponents() override;
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComp = nullptr;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp = nullptr;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

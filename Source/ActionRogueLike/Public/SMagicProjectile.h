
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void TriggerImpactEffects();

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnActorHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "MagicProjectile")
	USoundBase* ImpactSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "MagicProjectile")
	UParticleSystem* ImpactEmitter = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "MagicProjectile")
	float DamageDealt = 20.0f;
	
};

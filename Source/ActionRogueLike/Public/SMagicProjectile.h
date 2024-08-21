
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SProjectile.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USActionEffect;

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
	TObjectPtr<USoundBase> ImpactSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "MagicProjectile")
	TObjectPtr<UParticleSystem> ImpactEmitter = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<USActionEffect> BurningActionClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageDealt = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag ParryTag;
};

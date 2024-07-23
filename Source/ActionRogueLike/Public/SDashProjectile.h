// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectile
{
	GENERATED_BODY()

public:
	ASDashProjectile();
	
	virtual void BeginPlay() override;

protected:
	void Cleanup();
	
	UFUNCTION()
	void TeleportOwner();

	UFUNCTION()
	void TriggerProjectile();

	virtual void PostInitializeComponents() override;
	
protected:

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TriggerParticle;
	
	FTimerHandle TriggerProjectileHandle;
	FTimerHandle TeleportHandle;
	
	float TeleportTime = 0.2f;
	float TriggerTime = 0.2f;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

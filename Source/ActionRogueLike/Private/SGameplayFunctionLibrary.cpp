// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributesComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"
#include "Camera/CameraComponent.h"

FVector USGameplayFunctionLibrary::GetShootPoint(UCameraComponent* CameraComponent, AActor* TracingActor)
{
	FVector TraceStart = CameraComponent->GetComponentLocation();
	FVector TraceEnd = TraceStart + CameraComponent->GetForwardVector() * 2000;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(TracingActor);
	
	bool bWasHit = TracingActor->GetWorld()->LineTraceSingleByProfile(HitResult,TraceStart,TraceEnd,TEXT("Projectile"),Params);

	if(bWasHit)
	{
		return HitResult.ImpactPoint;
	}
	else
	{
		return TraceEnd;
	}
}

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageDealer, AActor* TargetActor, float DamageAmount)
{
	USAttributesComponent* AttributesComp = USAttributesComponent::GetAttributes(TargetActor);
	if(AttributesComp)
	{
		return AttributesComp->ApplyHealthChange(DamageDealer,DamageAmount);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageDealer, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageDealer,TargetActor,DamageAmount))
	{
		UPrimitiveComponent* Primitive = HitResult.GetComponent();
		if(Primitive && Primitive->IsSimulatingPhysics(HitResult.BoneName))
		{
			const float BigMagicNumber = 300000.0f;
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();
			
			Primitive->AddImpulseAtLocation(Direction *  BigMagicNumber,HitResult.ImpactPoint,HitResult.BoneName);
			
		}
		return true;
	}

	return false;
}

void USGameplayFunctionLibrary::AddCreditsAmount(APawn* TriggeringPawn, int32 Amount)
{
	ASCharacter* Character = Cast<ASCharacter>(TriggeringPawn);
	if(Character == nullptr )
	{
		return;
	}

	ASPlayerState* PlayerState = Character->GetPlayerState<ASPlayerState>();
	if(!ensure(PlayerState))
	{
		return;
	}

	PlayerState->ApplyCreditsChange(Amount);
}

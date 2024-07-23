// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

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

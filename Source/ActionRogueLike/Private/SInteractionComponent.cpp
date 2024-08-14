// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDrawInteractionDebug(TEXT("su.DrawInteractionDebgu"),false, TEXT("Draw Debug helpers for "),ECVF_Cheat);

void USInteractionComponent::PrimaryInteract()
{
	bool DrawDebug = CVarDrawInteractionDebug.GetValueOnGameThread();
	
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + ( EyeRotation.Vector() * 1000);
	
	// FHitResult Hit;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,QueryParams);
	// AActor* HitActor = Hit.GetActor();

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float Radius =  45.0f;
	
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,QueryParams,Shape);
	FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;
	
	for(FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				APawn* AsPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor,AsPawn);

				if(DrawDebug)
				{
					DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,DebugLineColor,false,2.0f);
				}
				break;
			}
		}
	}

	if(DrawDebug)
	{
		DrawDebugLine(GetWorld(),EyeLocation,End,DebugLineColor,false,2.0f,0,2.0f);
	}
}

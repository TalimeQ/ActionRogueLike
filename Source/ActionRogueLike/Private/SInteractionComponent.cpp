// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "Blueprint/UserWidget.h"
#include "UI/SWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDrawInteractionDebug(TEXT("su.DrawInteractionDebgu"),false, TEXT("Draw Debug helpers for "),ECVF_Cheat);


USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceRadius = 30.0f;
	TraceDistance = 1000.0f;
	CollisionChannel = ECC_WorldDynamic;
}

void USInteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusedActor.Get());
}

void USInteractionComponent::ServerInteract_Implementation(AActor* InteractionTarget)
{
	APawn* AsPawn = Cast<APawn>(GetOwner());
	if(InteractionTarget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor to Interact");
		return;
	}
	
	ISGameplayInterface::Execute_Interact(InteractionTarget,AsPawn);
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* OwnerAsPawn = Cast<APawn>(GetOwner());
	if(OwnerAsPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

void USInteractionComponent::HandleInteractionWidget()
{
	if(FocusedActor != nullptr)
	{
		if(DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(),DefaultWidgetClass);
		}

		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->SetAttachedActor(FocusedActor.Get());
			if(!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
}

void USInteractionComponent::FindBestInteractable()
{
	bool DrawDebug = CVarDrawInteractionDebug.GetValueOnGameThread();
	
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FVector End = EyeLocation + ( EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	
	Shape.SetSphere(TraceRadius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,QueryParams,Shape);
	FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;

	FocusedActor = nullptr;
	
	for(FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(DrawDebug)
			{
				DrawDebugSphere(GetWorld(),Hit.ImpactPoint,TraceRadius,32,DebugLineColor,false,0.0f);
			}
			
			if(HitActor->Implements<USGameplayInterface>())
			{
				FocusedActor = Hit.GetActor();
				break;
			}
		}
	}

	HandleInteractionWidget();
	
	if(DrawDebug)
	{
		DrawDebugLine(GetWorld(),EyeLocation,End,DebugLineColor,false,2.0f,0,0.0f);
	}
}


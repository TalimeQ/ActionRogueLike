// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractableActor.h"

#include "Components/SCreditsComponent.h"

ASInteractableActor::ASInteractableActor()
{
	CreditsComponent = CreateDefaultSubobject<USCreditsComponent>("CreditsComp");
}

void ASInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASInteractableActor::TriggerInteraction(APawn* InstigatorPawn)
{
	bIsActive = false;
	HideActor();
	TriggerPayload(InstigatorPawn);
}

void ASInteractableActor::OnReactivationFinished()
{
	bIsActive = true;
	ShowActor();
}

bool ASInteractableActor::CanTriggerInteraction_Implementation(APawn* InstigatorPawn)
{
	return true;
}

void ASInteractableActor::TriggerPayload_Implementation(APawn* InstigatorPawn)
{
}

void ASInteractableActor::ShowActor_Implementation()
{
	
}

void ASInteractableActor::HideActor_Implementation()
{
	
}


void ASInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASInteractableActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!bIsActive)
	{
		return;
	}

	if(!CanTriggerInteraction(InstigatorPawn))
	{
		return;
	}
	
	TriggerInteraction(InstigatorPawn);
	
	if(bReactivates)
	{
		GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle,this,&ASInteractableActor::OnReactivationFinished,TimeToReactivate);
		return;
	}

	Destroy();
}


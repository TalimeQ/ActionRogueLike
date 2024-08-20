// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpPickup.h"

#include "Actions/SActionComponent.h"
#include "Components/SphereComponent.h"

ASPowerUpPickup::ASPowerUpPickup()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComp;
	
	PowerupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionMesh");
	PowerupMesh->SetupAttachment(RootComponent);

	GrantedAction = nullptr;
}

void ASPowerUpPickup::TriggerPayload_Implementation(APawn* InstigatorPawn)
{
	USActionComponent* ActionComp = InstigatorPawn->FindComponentByClass<USActionComponent>();
	if(!ensure(GrantedAction) || ActionComp == nullptr)
	{
		return;
	}
	
	ActionComp->AddAction(InstigatorPawn,GrantedAction);
}

void ASPowerUpPickup::ShowActor_Implementation()
{
	PowerupMesh->SetHiddenInGame(false);
}

void ASPowerUpPickup::HideActor_Implementation()
{
	PowerupMesh->SetHiddenInGame(true);
}

bool ASPowerUpPickup::CanTriggerInteraction_Implementation(APawn* InstigatorPawn)
{
	return Super::CanTriggerInteraction_Implementation(InstigatorPawn);
}

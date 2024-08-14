// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributesComponent.h"
#include "Components/SphereComponent.h"

ASHealthPotion::ASHealthPotion() : Super()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComp;
	
	PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionMesh");
	PotionMesh->SetupAttachment(RootComponent);
}

void ASHealthPotion::TriggerPayload_Implementation(APawn* InstigatorPawn)
{
	USAttributesComponent* AttributesComp = InstigatorPawn->FindComponentByClass<USAttributesComponent>();

	if(ensure(AttributesComp))
	{
		AttributesComp->ApplyHealthChange(this, HealthRestored);
	}
}

void ASHealthPotion::ShowActor_Implementation()
{
	PotionMesh->SetHiddenInGame(false);
}

void ASHealthPotion::HideActor_Implementation()
{
	PotionMesh->SetHiddenInGame(true);
}


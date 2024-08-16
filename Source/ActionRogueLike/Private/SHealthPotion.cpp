// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributesComponent.h"
#include "SCharacter.h"
#include "SGameplayFunctionLibrary.h"
#include "SPlayerState.h"
#include "Components/SCreditsComponent.h"
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
		USGameplayFunctionLibrary::AddCreditsAmount(InstigatorPawn,CreditsComponent->GetCreditsAmount());
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

bool ASHealthPotion::CanTriggerInteraction_Implementation(APawn* InstigatorPawn)
{
	ASCharacter* Character = Cast<ASCharacter>(InstigatorPawn);
	if(Character == nullptr )
	{
		return false;
	}

	ASPlayerState* PlayerState = Character->GetPlayerState<ASPlayerState>();
	if(!ensure(PlayerState))
	{
		return false;
	}
	
	int32 CreditsChange = CreditsComponent->GetCreditsAmount();
	return PlayerState->CanAffordActivation(CreditsChange);
}



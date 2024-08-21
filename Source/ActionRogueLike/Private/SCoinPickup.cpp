// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickup.h"

#include "SCharacter.h"
#include "SGameplayFunctionLibrary.h"
#include "SPlayerState.h"
#include "Components/SphereComponent.h"

ASCoinPickup::ASCoinPickup() : Super()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComp;
	
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionMesh");
	CoinMesh->SetupAttachment(RootComponent);

	CoinsRewarded = 20;
}

void ASCoinPickup::TriggerPayload_Implementation(APawn* InstigatorPawn)
{
	USGameplayFunctionLibrary::AddCreditsAmount(InstigatorPawn,CoinsRewarded);
}

void ASCoinPickup::ShowActor_Implementation()
{
	CoinMesh->SetHiddenInGame(false);
}

void ASCoinPickup::HideActor_Implementation()
{
	CoinMesh->SetHiddenInGame(true);
}

bool ASCoinPickup::CanTriggerInteraction_Implementation(APawn* InstigatorPawn)
{
	return true;
}

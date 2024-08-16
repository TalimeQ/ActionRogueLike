// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::ApplyCreditsChange(int32 Amount)
{
	CreditsAmount += Amount;

	// Clamping would be better but for now no max credits
	if(CreditsAmount < 0)
	{
		CreditsAmount = 0;
	}

	OnCreditsChanged.Broadcast(CreditsAmount);
}

bool ASPlayerState::CanAffordActivation(int32 Cost) const
{
	return CreditsAmount + Cost >= 0;
}

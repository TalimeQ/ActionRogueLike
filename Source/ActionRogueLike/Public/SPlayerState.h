// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged,int32,CreditsAmount);

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ApplyCreditsChange(int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool CanAffordActivation(int32 Cost) const;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;
	
protected:
	UPROPERTY(VisibleAnywhere)
	int32 CreditsAmount = 0;
};

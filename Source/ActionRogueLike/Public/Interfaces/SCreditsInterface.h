// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SCreditsInterface.generated.h"


UINTERFACE(MinimalAPI,BlueprintType,Blueprintable)
class USCreditsInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API ISCreditsInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	int32 GetCreditsReward() const;
};

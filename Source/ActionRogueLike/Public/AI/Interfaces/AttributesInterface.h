// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttributesInterface.generated.h"

class USAttributesComponent;

UINTERFACE(MinimalAPI)
class UAttributesInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API IAttributesInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	USAttributesComponent* GetAttributesComponent();
};

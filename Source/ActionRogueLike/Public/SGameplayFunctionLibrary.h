// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

class UCameraComponent;
class AActor;

UCLASS()
class ACTIONROGUELIKE_API USGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION()
	static FVector GetShootPoint(UCameraComponent* CameraComponent, AActor* TracingActor);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributesComponent.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributesComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTargetDummy();

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USAttributesComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
};

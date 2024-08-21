// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:
	ASItemChest();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch = 0.0f;
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LidMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> GoldMesh;

};

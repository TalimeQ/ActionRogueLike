// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SAICharacter.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"


class USizeBox;

UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetAttachedActor(AActor* InActor);
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "UI")
	FVector WorldOffset = FVector::ZeroVector;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	AActor* AttachedActor = nullptr;
};

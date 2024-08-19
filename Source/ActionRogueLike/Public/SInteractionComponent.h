// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


class USWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USInteractionComponent();
	
	void PrimaryInteract();

	void FindBestInteractable();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleInteractionWidget();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldUserWidget> DefaultWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float  TraceDistance;
	
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float  TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	
private:
	UPROPERTY()
	TObjectPtr<USWorldUserWidget> DefaultWidgetInstance;
	
	UPROPERTY()
	TWeakObjectPtr<AActor> FocusedActor = nullptr;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"


class USActionComponent;

UCLASS(Blueprintable,BlueprintType)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator) const ;
	
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Action")
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Action")
	FName GetActionName() const {return ActionName;};

	UFUNCTION(BlueprintCallable, Category = "Action")
	USActionComponent* GetOwningComponent() const;

	virtual UWorld* GetWorld() const override;

	bool IsRunning() const {return bIsRunning;};

public:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart = false;
	
protected:
	/* Action Identifier */
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;

	/* Tags granted after action start*/
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	/*Action can start if we have none of these tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockingTags;

private:
	bool bIsRunning = false;
};

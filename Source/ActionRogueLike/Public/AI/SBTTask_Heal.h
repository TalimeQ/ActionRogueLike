// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_Heal.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USBTTask_Heal();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = "Healing")
	int32 HealthHealed;
};

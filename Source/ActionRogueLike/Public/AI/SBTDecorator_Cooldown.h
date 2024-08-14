// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SBTDecorator_Cooldown.generated.h"

struct FSBTCooldownDecoratorMemory
{
	double LastUseTimestamp;
	uint8 bRequestedRestart : 1;
};

UCLASS(HideCategories=(Condition))
class ACTIONROGUELIKE_API USBTDecorator_Cooldown : public UBTDecorator
{
	GENERATED_BODY()

	USBTDecorator_Cooldown();

	/** Specifies the cooldown time of this decorator. */
	UPROPERTY(EditAnywhere, Category=Decorator)
	float CooldownTime;

	virtual void PostLoad() override;
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

protected:
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};

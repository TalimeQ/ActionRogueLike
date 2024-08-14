// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTDecorator_Cooldown.h"

USBTDecorator_Cooldown::USBTDecorator_Cooldown()
{
	NodeName = "Cooldown";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	CooldownTime = 5.0f;

	// aborting child nodes doesn't make sense, cooldown starts after leaving this branch
	bAllowAbortChildNodes = false;
}

void USBTDecorator_Cooldown::PostLoad()
{
	Super::PostLoad();
	bNotifyTick = (FlowAbortMode != EBTFlowAbortMode::None);
}

void USBTDecorator_Cooldown::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	FSBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FSBTCooldownDecoratorMemory>(NodeMemory);
	if (InitType == EBTMemoryInit::Initialize) DecoratorMemory->LastUseTimestamp = TNumericLimits<double>::Lowest();
	DecoratorMemory->bRequestedRestart = false;
}

bool USBTDecorator_Cooldown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const FSBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FSBTCooldownDecoratorMemory>(NodeMemory);
	const double RecalculateTimeStamp = (OwnerComp.GetWorld()->GetTimeSeconds() - CooldownTime);
	return RecalculateTimeStamp >= DecoratorMemory->LastUseTimestamp;
}

void USBTDecorator_Cooldown::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
	const FSBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FSBTCooldownDecoratorMemory>(NodeMemory);

	if (const double TimePassed = OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp; TimePassed < CooldownTime)
	{
		Values.Add(FString::Printf(TEXT("%s in %ss"), (FlowAbortMode == EBTFlowAbortMode::None) ? TEXT("unlock") : TEXT("restart"), *FString::SanitizeFloat(CooldownTime - TimePassed)));
	}
}

uint16 USBTDecorator_Cooldown::GetInstanceMemorySize() const
{
	return sizeof(FSBTCooldownDecoratorMemory);
}

FString USBTDecorator_Cooldown::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: lock for %.1fs after execution and return %s"), *Super::GetStaticDescription(), CooldownTime, *UBehaviorTreeTypes::DescribeNodeResult(EBTNodeResult::Failed));
}

void USBTDecorator_Cooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FSBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FSBTCooldownDecoratorMemory>(NodeMemory);

	if (!DecoratorMemory->bRequestedRestart)
	{
		const double RecalculateTimeStamp = (OwnerComp.GetWorld()->GetTimeSeconds() - CooldownTime);

		if (RecalculateTimeStamp >= DecoratorMemory->LastUseTimestamp)
		{
			DecoratorMemory->bRequestedRestart = true;
			OwnerComp.RequestExecution(this);
		}
	}
}

void USBTDecorator_Cooldown::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	FSBTCooldownDecoratorMemory* DecoratorMemory = GetNodeMemory<FSBTCooldownDecoratorMemory>(SearchData);
	DecoratorMemory->LastUseTimestamp = SearchData.OwnerComp.GetWorld()->GetTimeSeconds();
	DecoratorMemory->bRequestedRestart = false;
}

#if WITH_EDITOR
FName USBTDecorator_Cooldown::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.Cooldown.Icon");
}
#endif
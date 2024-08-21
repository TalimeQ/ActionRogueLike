// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"
#include "AIController.h"
#include "SAttributesComponent.h"
#include "AI/SAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* MyController = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if(!ensure(MyController))
	{
		return;
	}

	if(!ensure(Blackboard))
	{
		return;
	}

	APawn* APawn = MyController->GetPawn();
	if(!ensure(APawn))
	{
		return;
	}

	if(!ensure(APawn->Implements<UAttributesInterface>()))
	{
		return;
	}
	
	USAttributesComponent* AttributesComp = IAttributesInterface::Execute_GetAttributesComponent(APawn);
	if(AttributesComp)
	{
		float Health = AttributesComp->GetHealth();
		float HealthMax = AttributesComp->GetHealthMax();

		if(Health / HealthMax <= RequiredHealthPercentage)
		{
			Blackboard->SetValueAsBool(NeedHealKey.SelectedKeyName,true);
		}
		else
		{
			Blackboard->SetValueAsBool(NeedHealKey.SelectedKeyName,false);
		}
	}
}

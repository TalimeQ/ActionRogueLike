// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributesComponent.h"
#include "Ai/Interfaces/AttributesInterface.h"

USBTTask_Heal::USBTTask_Heal() : Super()
{
	HealthHealed = 25.0f;
}

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController =  OwnerComp.GetAIOwner();
	if(!ensure(MyController))
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = MyController->GetPawn();
	if(Pawn != nullptr && !ensure(Pawn))
	{
		return EBTNodeResult::Failed;
	}
	
	USAttributesComponent* AttributesComponent = IAttributesInterface::Execute_GetAttributesComponent(Pawn);
	if(AttributesComponent != nullptr)
	{;
		AttributesComponent->ApplyHealthChange(OwnerComp.GetAIOwner()->GetPawn(), HealthHealed);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

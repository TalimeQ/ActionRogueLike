// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributesComponent.h"
#include "Ai/Interfaces/AttributesInterface.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController =  OwnerComp.GetAIOwner();

	if(!ensure(MyController))
	{
		return EBTNodeResult::Failed;
	}


	USAttributesComponent* AttributesComponent = IAttributesInterface::Execute_GetAttributesComponent(MyController->GetPawn());
	if(AttributesComponent != nullptr)
	{
		AttributesComponent->ApplyHealthChange(OwnerComp.GetAIOwner()->GetPawn(), 50);
		return EBTNodeResult::Succeeded;
	}
	

	return EBTNodeResult::Failed;
}

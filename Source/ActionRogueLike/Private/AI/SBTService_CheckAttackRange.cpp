// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USBTService_CheckAttackRange::USBTService_CheckAttackRange() : Super()
{
	DistanceRequired = 2000.0f;
}

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(!ensure(BlackboardComponent))
	{
		return;
	}
	
	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
	if(TargetActor == nullptr)
	{
		return;
	}

	AAIController* MyController = OwnerComp.GetAIOwner();
	if(!ensure(MyController))
	{
		return;
	}

	APawn* AIPawn = MyController->GetPawn();
	if(ensure(AIPawn))
	{
		float DistanceSquared = FVector::DistSquared(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
		float DistanceRequiredSquare = DistanceRequired * DistanceRequired;
		bool bWithinSquaredRange = DistanceSquared < DistanceRequiredSquare;
		
		if(!bWithinSquaredRange)
		{
			return;
		}
		
		float Distance = FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
		bool bWithinRange = Distance < DistanceRequired;
		
		if(bWithinRange)
		{
			return;
		}
		
		bool bHasLos = false;
		if(bWithinRange)
		{
			bHasLos = MyController->LineOfSightTo(TargetActor);
		}

		bool bCanTarget = bWithinRange && bHasLos;

		BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,bCanTarget);
	}
}

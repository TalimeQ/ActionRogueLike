// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviourTree,TEXT("Behaviour tree is nullptr! Please assign it in AI Controller!")))
	{
		RunBehaviorTree(BehaviourTree);
	}
}

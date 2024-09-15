// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction.h"

#include "Actions/SActionComponent.h"



void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	USActionComponent* OwningComponent = GetOwningComponent();
	OwningComponent->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);
	
	USActionComponent* OwningComponent = GetOwningComponent();
	OwningComponent->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

UWorld* USAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return GetOuter()->GetWorld();
	}

	return nullptr;
}

bool USAction::CanStart_Implementation(AActor* Instigator) const
{
	if(IsRunning())
	{
		return false;
	}
	
	USActionComponent* OwningComponent = GetOwningComponent();
	if(OwningComponent->ActiveGameplayTags.HasAny(BlockingTags))
	{
		return false;
	}
	return true;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

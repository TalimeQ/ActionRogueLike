// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Effects/SActionEffect.h"

#include "Actions/SActionComponent.h"

void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	
}

USActionEffect::USActionEffect()
{
	bAutoStart = true;
}

void USActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(Duration > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this,&USActionEffect::StopAction,Instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle,Delegate,Duration,false);
	}

	if(Period > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this,&USActionEffect::ExecutePeriodicEffect,Instigator);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle,Delegate,Period,true);
	}
}

void USActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if((GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) <= KINDA_SMALL_NUMBER))
	{
		ExecutePeriodicEffect(Instigator);
	}
	
	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	USActionComponent* OwningComponent = GetOwningComponent();
	if(OwningComponent)
	{
		OwningComponent->RemoveAction(this);
	}
}

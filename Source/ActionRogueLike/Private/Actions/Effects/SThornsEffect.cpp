// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Effects/SThornsEffect.h"

#include "SAttributesComponent.h"
#include "Actions/SActionComponent.h"

USThornsEffect::USThornsEffect() : Super()
{
	// Infinite duration
	Duration = UE_MAX_FLT;
	Period = 1.0f;

	bAutoStart = true;
}

void USThornsEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	USAttributesComponent* AttributesComp =  Instigator->FindComponentByClass<USAttributesComponent>();
	AttributesComp->OnHealthChanged.AddDynamic(this,&USThornsEffect::ReflectDamage);
}

void USThornsEffect::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	
	USAttributesComponent* AttributesComp =  Instigator->FindComponentByClass<USAttributesComponent>();
	AttributesComp->OnHealthChanged.RemoveDynamic(this,&USThornsEffect::ReflectDamage);
}

void USThornsEffect::ReflectDamage(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth,
	float Delta)
{
	AActor* OwnerActor = GetOwningComponent()->GetOwner();
	
	if(InstigatorActor == nullptr || InstigatorActor == OwnerActor)
	{
		return;
	}

	float ReturnedDamage =  FMath::RoundToInt32( Delta * PercentReflected);

	auto* DamageDealerAttributes = USAttributesComponent::GetAttributes(InstigatorActor);
	DamageDealerAttributes->ApplyHealthChange(OwnerActor,ReturnedDamage);
}

void USThornsEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	Super::ExecutePeriodicEffect_Implementation(Instigator);
	
	// Ensure this is infinite
	Duration = UE_MAX_FLT;
}

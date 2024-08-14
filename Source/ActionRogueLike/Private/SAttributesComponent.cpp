// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributesComponent.h"



static TAutoConsoleVariable<float> CVarGlobalDamageMulti(TEXT("su.DamageMultiplier"),1.0f,TEXT("Changes the global damage multipler"),ECVF_Cheat);

USAttributesComponent::USAttributesComponent()
{
	Health = 100.0f;
}

bool USAttributesComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if(Delta < 0.0f)
	{
		float DamageMultiplier = CVarGlobalDamageMulti.GetValueOnGameThread();
		
		Delta *= DamageMultiplier;
	}
	
	float OldHealth = Health;
	
	Health = FMath::Clamp(Health + Delta,0.0f,MaxHealth);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor,this,Health,ActualDelta);

	// Died
	if(ActualDelta < 0.0f && Health == 0.0f)
	{
		ASGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if(GameMode)
		{
			GameMode->OnActorKilled(GetOwner(),InstigatorActor);
		}
	}
	
	return true;
}

bool USAttributesComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}

bool USAttributesComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributesComponent::GetHealth() const
{
	return Health;
}

float USAttributesComponent::GetHealthMax() const
{
	return MaxHealth;
}

USAttributesComponent* USAttributesComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor)
	{
		return FromActor->FindComponentByClass<USAttributesComponent>();
	}

	return nullptr;
}

bool USAttributesComponent::IsActorAlive(AActor* FromActor)
{
	USAttributesComponent* AttributesComponent = GetAttributes(FromActor);
	if(AttributesComponent )
	{
		return AttributesComponent->IsAlive();
	}

	return false;
}

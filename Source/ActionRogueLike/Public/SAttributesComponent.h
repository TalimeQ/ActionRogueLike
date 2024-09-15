// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameModeBase.h"
#include "Components/ActorComponent.h"
#include "SAttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*, InstigatorActor,USAttributesComponent*,OwningComp,float,NewHealth,float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRageChanged,USAttributesComponent*,OwningComp,float,NewRage,float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributesComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* FromActor);
	
public:	
	USAttributesComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyRageChange( float Delta);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;
	
	float GetHealth() const;
	float GetHealthMax() const;

	float GetRage() const;
	float GetRageMax() const;

protected:
	// Reliable multicasts ingore relevancy
	
	UFUNCTION(NetMulticast,Reliable) // @FIXME : mark as unreliable as we move the controller hookup from character
	void MultiCastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRageChanged OnRageChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Replicated, Category = "Attributes")
	float Health = 0;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Replicated, Category = "Attributes")
	float MaxHealth = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float HealthToRageRatio = 0.25f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float Rage = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float RageMax = 0;
};

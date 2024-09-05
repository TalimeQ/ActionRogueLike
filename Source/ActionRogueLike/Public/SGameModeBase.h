// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"


class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
class UCurveFloat;

UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameModeBase();
	
	UFUNCTION()
	void SpawnBotsTimerElapsed();

	UFUNCTION(Exec)
	void KillAllAI();

	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* Victim, AActor* Killer);

protected:
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UFUNCTION()
	void OnPowerupQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	
protected:
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnBotQuery = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UCurveFloat> DifficultyCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	TArray<TSubclassOf<AActor>> PowerUpClasses;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	TObjectPtr<UEnvQuery> PowerUpSpawnQuery;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	int32 DesiredPowerUpAmount = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributesComponent.h"
#include "SCharacter.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"),true,TEXT("Enable spawning bots via timer"), ECVF_Cheat);

ASGameModeBase::ASGameModeBase() : Super()
{
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                      EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn bot EQS Query Failed"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if(Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass,Locations[0],FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(),Locations[0],50.0f,20,FColor::Blue,false,60.0f);
	}
}

void ASGameModeBase::SpawnBotsTimerElapsed()
{
	if(!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Warning,TEXT("Bots Spawning disabled by CVar"));
		return;
	}
	
	int32 NrOfAliveBots = 0;
	for(TActorIterator<ASAICharacter> it(GetWorld());it;++it )
	{
		ASAICharacter* Bot = *it;

		if(Bot->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	// Change for curve ;)
	float MaxBoutCounts = 10.0f;

	if(DifficultyCurve)
	{
		MaxBoutCounts = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	
	if(NrOfAliveBots >= MaxBoutCounts)
	{
		UE_LOG(LogTemp,Log,TEXT("At maximum capacity, skipping bot spawn"))
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance =  UEnvQueryManager::RunEQSQuery(this,SpawnBotQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);

	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);
}

void ASGameModeBase::KillAllAI()
{
	for(TActorIterator<ASAICharacter> it(GetWorld());it;++it )
	{
		ASAICharacter* Bot = *it;
		Bot->GetAttributesComp()->Kill(this); // TODO :: FIXME add credit for player
	}
}


void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots,this,&ASGameModeBase::SpawnBotsTimerElapsed,SpawnTimerInterval,true);
}

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();
		
		RestartPlayer(Controller);
	}
}

void ASGameModeBase::OnActorKilled(AActor* Victim, AActor* Killer)
{
	ASCharacter* Player = Cast<ASCharacter>(Victim);
	if(Player)
	{
		FTimerHandle TimerHandleRespawnDelay;
		FTimerDelegate Delegate;

		Delegate.BindUObject(this,&ASGameModeBase::RespawnPlayerElapsed,Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandleRespawnDelay,Delegate,RespawnDelay,false);
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"),*GetNameSafe(Victim),*GetNameSafe(Killer));
}

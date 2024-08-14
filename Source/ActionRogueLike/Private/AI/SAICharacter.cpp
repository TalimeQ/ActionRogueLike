// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributesComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/SWorldUserWidget.h"


ASAICharacter::ASAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributesComponent = CreateDefaultSubobject<USAttributesComponent>("AttributesComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HitFlashColor = FColor::Cyan;
	HitParam = "TimeToHit";
	ColorParam = "Color";

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSensed);
	AttributesComponent->OnHealthChanged.AddDynamic(this,&ASAICharacter::OnHealthChanged);
}

USAttributesComponent* ASAICharacter::GetAttributesComp() const
{
	return AttributesComponent;
}

bool ASAICharacter::IsAlive()
{
	if(!ensure(AttributesComponent))
	{
		return false;
	}
	
	return AttributesComponent->IsAlive();
}



void ASAICharacter::OnPawnSensed(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(),GetActorLocation(),"PLAYER SPOTTED",nullptr, FColor::Green);
}

USAttributesComponent* ASAICharacter::GetAttributesComponent_Implementation()
{
	return AttributesComponent;
}

void ASAICharacter::TriggerHitFlash()
{


	GetMesh()->SetVectorParameterValueOnMaterials(ColorParam,UKismetMathLibrary::Conv_LinearColorToVector(HitFlashColor));
	GetMesh()->SetScalarParameterValueOnMaterials(HitParam,GetWorld()->GetTimeSeconds());
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth,
                                    float Delta)
{
	if(Delta < 0.0f)
	{
		if(InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if(ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(),HealthBarWidgetClass);
			if(ActiveHealthBar)
			{
				ActiveHealthBar->SetAttachedActor(this);
				ActiveHealthBar->AddToViewport();
			}
		}

		
		TriggerHitFlash();
		
		if(FMath::IsNearlyZero(NewHealth) || NewHealth < 0)
		{
			// stop bt
			AAIController* AIController = Cast<AAIController>(GetController());
			if(AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}
			
			// ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			
			// set lifespan
			SetLifeSpan(10.0f);
		}
	}
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if(ensure(AIController))
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor",NewTarget);
	}
}




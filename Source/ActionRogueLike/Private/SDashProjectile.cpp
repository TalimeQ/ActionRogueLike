// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile() : Super()
{
	TriggerParticle = CreateDefaultSubobject<UParticleSystemComponent>("TriggerParticle");
	TriggerParticle->SetAutoActivate(false);
	TriggerParticle->SetupAttachment(SphereComp);
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().ClearTimer(TeleportHandle);
	GetWorld()->GetTimerManager().SetTimer(TriggerProjectileHandle,this,&ASDashProjectile::TriggerProjectile,TriggerTime);
}

void ASDashProjectile::Cleanup()
{
	Destroy();
}

void ASDashProjectile::TeleportOwner()
{
	APawn* InstigatorPawn = GetInstigator();
	if(InstigatorPawn)
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(InstigatorPawn);
		
		FVector Start = GetActorLocation();
		FVector End = GetActorLocation() + (InstigatorPawn->GetActorUpVector() * - 1.0f) * 1500.0f;
		
		bool bWasHit = GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECC_WorldStatic,QueryParams);
		if(bWasHit)
		{
			InstigatorPawn->TeleportTo(HitResult.Location,GetActorRotation());
		}
		else
		{
			InstigatorPawn->TeleportTo(GetActorLocation(),GetActorRotation());
		}
	}

	Cleanup();
}

void ASDashProjectile::TriggerProjectile()
{
	TriggerParticle->Activate();
	ParticleSystemComp->SetHiddenInGame(true);
	
	MovementComp->StopMovementImmediately();
	
	GetWorld()->GetTimerManager().SetTimer(TeleportHandle,this,&ASDashProjectile::TeleportOwner,TeleportTime);
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this,&ASDashProjectile::OnComponentHit);
}

void ASDashProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TriggerProjectile();
}



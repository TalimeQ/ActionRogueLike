// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributesComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Actions/SActionComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this,&ASMagicProjectile::OnActorHit);
	if(GetInstigator())
	{
		SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	}

}

void ASMagicProjectile::TriggerImpactEffects()
{
	if(ensure(ImpactSound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSound,GetActorLocation());
	}
	if(ensure(ImpactEmitter))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEmitter,GetActorLocation(),GetActorRotation());
	}
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		USActionComponent* ActionComponent = OtherActor->FindComponentByClass<USActionComponent>();
		if(ActionComponent && ActionComponent->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
		}
		
		if(USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,DamageDealt,SweepResult))
		{
			TriggerImpactEffects();
			Destroy();

			if(ActionComponent && BurningActionClass != nullptr)
			{
				ActionComponent->AddAction(GetInstigator(),BurningActionClass);
			}
		}
	}
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	TriggerImpactEffects();
	Destroy();
}



void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


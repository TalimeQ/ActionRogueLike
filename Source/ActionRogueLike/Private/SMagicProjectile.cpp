// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributesComponent.h"
#include "Components/SphereComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectile::OnActorOverlap);
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		USAttributesComponent* AttributeComp = OtherActor->FindComponentByClass<USAttributesComponent>();
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageDealt);
			Destroy();
		}
	}
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


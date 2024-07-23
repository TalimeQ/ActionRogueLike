// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplodingBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"


ASExplodingBarrel::ASExplodingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	ForceComp->bImpulseVelChange = true;
	ForceComp->ImpulseStrength = 3000.0f;
	ForceComp->SetupAttachment(RootComponent);
}

void ASExplodingBarrel::Explode()
{
	Receive_Explode();
}

void ASExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddDynamic(this,&ASExplodingBarrel::OnComponentHit);
}

void ASExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplodingBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	Receive_Explode();
	
	UE_LOG(LogTemp,Log,TEXT("OnActorHit in Explosive Barrel"));
	UE_LOG(LogTemp,Warning, TEXT("OtherActor is: %s , at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,CombinedString,nullptr,FColor::Orange,2.0f,true);
}

void ASExplodingBarrel::Receive_Explode()
{
	ForceComp->FireImpulse();
}



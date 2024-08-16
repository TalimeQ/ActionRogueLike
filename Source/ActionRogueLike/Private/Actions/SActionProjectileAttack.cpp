// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SActionProjectileAttack.h"

#include "SGameplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

USActionProjectileAttack::USActionProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USActionProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* AsCharacter = Cast<ACharacter>(Instigator);
	if(AsCharacter)
	{
		AsCharacter->PlayAnimMontage(AttackAnimMontage);
		UGameplayStatics::SpawnEmitterAttached(CastingEmitterTemplate,AsCharacter->GetMesh(),"Muzzle_01");
		
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,&USActionProjectileAttack::AttackDelayElapsed,AsCharacter);
		FTimerHandle AttackDelayHandle;

		GetWorld()->GetTimerManager().SetTimer(AttackDelayHandle,TimerDelegate,AttackAnimDelay,false);
	}
}

void USActionProjectileAttack::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}

void USActionProjectileAttack::AttackDelayElapsed(ACharacter* InstigatorCharacter)
{
	if(ensureAlways(ProjectileClass))
	{
		
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000.0f);

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FHitResult Hit;
		
		if(GetWorld()->SweepSingleByObjectType(Hit,TraceStart,TraceEnd,FQuat::Identity,ObjParams,Shape,Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation,TraceEnd);
		FTransform SpawnTM = FTransform(SpawnRotation,HandLocation);
        
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;
        
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	}

	StopAction(InstigatorCharacter);
}

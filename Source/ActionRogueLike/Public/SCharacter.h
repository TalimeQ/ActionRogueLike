// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class USInteractionComponent;
class UAnimMontage;
class UInputAction;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MainProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* AttackAnimMontage = nullptr;
	
	FTimerHandle TimerHandle_AbilityUsed;

public:

	ASCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	USInteractionComponent* InteractionComp;
	
	UPROPERTY(EditDefaultsOnly)
	const UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Move;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_LookMouse;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_PrimaryAttack;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_SecondaryAttack;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Jump;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Interact;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Dash;

protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);
	
	void PerformAbility(const FInputActionValue& Value, TSubclassOf<AActor> ProjectileType);
	void Attack_TimeElapsed(TSubclassOf<AActor> ProjectileType);
	void PerformJump();
	
public:	

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

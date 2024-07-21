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
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* AttackAnimMontage = nullptr;
	
	FTimerHandle TimerHandle_PrimaryAttack;

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
	const UInputAction* Input_Jump;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Interact;

	
	virtual void BeginPlay() override;
	
	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);
	
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PerformJump();
	
public:	

	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

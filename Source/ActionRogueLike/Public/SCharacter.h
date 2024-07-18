// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	const UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Move;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_LookMouse;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_PrimaryAttack;
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Jump;

	
	virtual void BeginPlay() override;
	
	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);

	void PrimaryAttack();
	
public:	

	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

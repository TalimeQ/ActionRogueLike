// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class USInteractionComponent;
class USAttributesComponent;
class UAnimMontage;
class UInputAction;
class USActionComponent;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()


public:

	ASCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100.0f);

	virtual FVector GetPawnViewLocation() const override;
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);
	
	void PerformAbility(const FInputActionValue& Value, FName ActionName);
	void PerformJump();

	void SprintStart();
	void SprintStop();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	void TriggerHitFlash() const;

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	FName MainAttackAction;
	UPROPERTY(EditAnywhere, Category = "Attack")
	FName SecondaryAttackAction;
	UPROPERTY(EditAnywhere, Category = "Attack")
	FName DashAction;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	USInteractionComponent* InteractionComp;
	
	UPROPERTY(EditDefaultsOnly)
	const UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	USAttributesComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComponent;
	
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
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* Input_Sprint;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FColor HitFlashColor = FColor::Cyan;

	UPROPERTY(EditDefaultsOnly,  Category = "Visual")
	FName ColorParam;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName HitParam;
};

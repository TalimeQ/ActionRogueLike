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
	UPROPERTY(EditAnywhere, Category = "Action")
	FName MainAttackAction;
	UPROPERTY(EditAnywhere, Category = "Action")
	FName SecondaryAttackAction;
	UPROPERTY(EditAnywhere, Category = "Action")
	FName DashAction;
	UPROPERTY(EditAnywhere, Category = "Action")
	FName ParryAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USInteractionComponent> InteractionComp;
	
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<USAttributesComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<USActionComponent> ActionComponent;
	
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Move;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_LookMouse;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_PrimaryAttack;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_SecondaryAttack;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Jump;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Interact;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Dash;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Sprint;
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UInputAction> Input_Parry;

	// TODO :: Move to separate component
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FColor HitFlashColor = FColor::Cyan;

	UPROPERTY(EditDefaultsOnly,  Category = "Visual")
	FName ColorParam;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName HitParam;

};

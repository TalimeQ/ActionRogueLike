#include "ActionRogueLike/Public/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SGameplayFunctionLibrary.h"
#include "SInteractionComponent.h"
#include "SProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	AddMovementInput(ControlRot.Vector(),AxisValue.Y);

	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,AxisValue.X);
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext,0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	InputComp->BindAction(Input_Move,ETriggerEvent::Triggered,this,&ASCharacter::Move);
	InputComp->BindAction(Input_LookMouse,ETriggerEvent::Triggered,this,&ASCharacter::LookMouse);

	// TODO :: Potentially we should put projectiles into second component atm, but there is queued ability comp somewhere in course so lets do not do this :)
	InputComp->BindAction(Input_PrimaryAttack,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,MainProjectileClass);
	InputComp->BindAction(Input_SecondaryAttack,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,SecondProjectileClass);
	InputComp->BindAction(Input_Dash,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,DashProjectileClass);
	InputComp->BindAction(Input_Jump,ETriggerEvent::Triggered,this,&ASCharacter::PerformJump);
	InputComp->BindAction(Input_Interact,ETriggerEvent::Triggered,InteractionComp,&USInteractionComponent::PrimaryInteract);
}

void ASCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ASCharacter::PerformAbility(const FInputActionValue& Value, TSubclassOf<AActor> ProjectileType)
{
	PlayAnimMontage(AttackAnimMontage);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ASCharacter::Attack_TimeElapsed,ProjectileType);
	GetWorldTimerManager().SetTimer(TimerHandle_AbilityUsed,TimerDelegate,0.2,false);
}



void ASCharacter::Attack_TimeElapsed(TSubclassOf<AActor> ProjectileType)
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FVector ImpactPoint = USGameplayFunctionLibrary::GetShootPoint(CameraComponent,this);
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation,ImpactPoint);
	FTransform SpawnTM = FTransform(SpawnRotation,HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileType,SpawnTM,SpawnParams);
}

void ASCharacter::PerformJump()
{
	Jump();
}


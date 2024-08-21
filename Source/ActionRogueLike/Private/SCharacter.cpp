#include "ActionRogueLike/Public/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SAttributesComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "SInteractionComponent.h"
#include "SProjectile.h"
#include "Actions/SActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

	AttributeComponent = CreateDefaultSubobject<USAttributesComponent>("Attributes Component");
	ActionComponent = CreateDefaultSubobject<USActionComponent>("Action Component");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;

	HitFlashColor = FColor::Cyan;
	HitParam = "TimeToHit";
	ColorParam = "Color";
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

// TODO :: Potentially move it to other component 
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
	InputComp->BindAction(Input_PrimaryAttack,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,MainAttackAction);
	InputComp->BindAction(Input_SecondaryAttack,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,SecondaryAttackAction);
	InputComp->BindAction(Input_Dash,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,DashAction);
	InputComp->BindAction(Input_Jump,ETriggerEvent::Triggered,this,&ASCharacter::PerformJump);
	InputComp->BindAction(Input_Interact,ETriggerEvent::Triggered,InteractionComp.Get(),&USInteractionComponent::PrimaryInteract);
	InputComp->BindAction(Input_Sprint,ETriggerEvent::Started,this,&ASCharacter::SprintStart);
	InputComp->BindAction(Input_Sprint,ETriggerEvent::Completed,this,&ASCharacter::SprintStop);
	InputComp->BindAction(Input_Parry,ETriggerEvent::Triggered,this,&ASCharacter::PerformAbility,ParryAction);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComponent->ApplyHealthChange(this,Amount);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComponent->GetComponentLocation();
}

void ASCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
}

void ASCharacter::PerformAbility(const FInputActionValue& Value, FName ActionName)
{
	ActionComponent->StartActionByName(this,ActionName);
}

void ASCharacter::PerformJump()
{
	Jump();
}

void ASCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this,"sprint");
}

void ASCharacter::SprintStop()
{
	ActionComponent->StopActionByName(this,"sprint");
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth,
                                  float Delta)
{
	if(Delta < 0.0f && NewHealth >= 0.0f)
	{
		TriggerHitFlash();
	}
	
	if(NewHealth <=0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ASCharacter::TriggerHitFlash() const
{
	GetMesh()->SetVectorParameterValueOnMaterials(ColorParam,UKismetMathLibrary::Conv_LinearColorToVector(HitFlashColor));
	GetMesh()->SetScalarParameterValueOnMaterials(HitParam,GetWorld()->GetTimeSeconds());
}

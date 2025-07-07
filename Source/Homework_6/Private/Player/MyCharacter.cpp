#include "Player/MyCharacter.h"
#include "Player/MyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::OnMove(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.Length()))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AMyCharacter::OnLook(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.Length()))
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);
	}
}

void AMyCharacter::OnJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AMyPlayerController* PC = GetMyPlayerController();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(PC) && EnhancedInput != nullptr)
	{
		if (PC->MoveAction)
		{
			EnhancedInput->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnMove);
		}
		if (PC->LookAction)
		{
			EnhancedInput->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnLook);
		}
		if (PC->JumpAction)
		{
			EnhancedInput->BindAction(PC->JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnJump);
		}
	}
}

AMyPlayerController* AMyCharacter::GetMyPlayerController()
{
	if (AController* TargetController = GetController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(TargetController))
		{
			return MyPlayerController;
		}
	}
	return nullptr;
}
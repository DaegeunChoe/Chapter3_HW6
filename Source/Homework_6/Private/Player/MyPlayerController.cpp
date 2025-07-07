#include "Player/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
{
	CharacterIMC = nullptr;
	JumpAction = nullptr;
	MoveAction = nullptr;
	LookAction = nullptr;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (CharacterIMC != nullptr)
			{
				int32 Priority = 0;
				Subsystem->AddMappingContext(CharacterIMC, Priority);
			}
		}
	}
}

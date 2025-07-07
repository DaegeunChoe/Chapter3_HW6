#include "Game/MyGameModeBase.h"
#include "Game/MyGameStateBase.h"
#include "Player/MyCharacter.h"
#include "Player/MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyCharacter::StaticClass();
}

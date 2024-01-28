#include "GameMode/GamePlayerController.h"


void AGamePlayerController::BeginPlay() {
	FInputModeGameAndUI Input;
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	Input.SetHideCursorDuringCapture(false);

	/*FInputModeUIOnly Input;
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetInputMode(Input);*/

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}
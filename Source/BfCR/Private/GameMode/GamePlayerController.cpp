#include "GameMode/GamePlayerController.h"

AGamePlayerController::AGamePlayerController() {
	//!!! need to include "InputMappingContext.h"
	//!!! ConstructorHelpers::FObjectFinder only inside constructor

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> ContextFinder_Mapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/InputMappingContext.InputMappingContext'"));

	if (ContextFinder_Mapping.Succeeded())
	{
		InputMapping = ContextFinder_Mapping.Object;
	}
}

void AGamePlayerController::BeginPlay() {
	// Settings for mouse cursor
	FInputModeGameAndUI Input;
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	Input.SetHideCursorDuringCapture(false);
	SetInputMode(Input);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Add mapping context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
}
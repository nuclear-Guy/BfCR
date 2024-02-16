#include "GameMode/GamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Input/ButtonWidget.h"

AGamePlayerController::AGamePlayerController() {
	//!!! need to include "InputMappingContext.h"
	//!!! ConstructorHelpers::FObjectFinder only inside constructor

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> ContextFinder_Mapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/InputMappingContext.InputMappingContext'"));

	if (ContextFinder_Mapping.Succeeded())
	{
		InputMapping = ContextFinder_Mapping.Object;
	}

	// get widget blueprint class --- this not works with blueprint, need to create class
	/*static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBPClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_CommonButtons.WB_CommonButtons'"));
	if (WidgetBPClassFinder.Succeeded())
	{
		WidgetBPClass = WidgetBPClassFinder.Class;
	}*/

}

void AGamePlayerController::AddGroupOfUnits()
{
}

void AGamePlayerController::SaveGame()
{
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

	// Add widgets to viewport
	if (IsValid(WidgetBPClass)) {
		UUserWidget* UI = Cast<UUserWidget>(CreateWidget(GetWorld(), WidgetBPClass));
		if (UI) {
			UI->AddToViewport();
		}
	}
	
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HUD_MouseSelection.h"

AHUD_MouseSelection::AHUD_MouseSelection() {
	static ConstructorHelpers::FObjectFinder<UInputDataConfig> ContextFinderConfig(TEXT("/Script/BfCR.InputDataConfig'/Game/Inputs/InputConfig.InputConfig'"));
	if (ContextFinderConfig.Succeeded())
	{
		InputActions = ContextFinderConfig.Object;
	}
}

void AHUD_MouseSelection::DrawHUD() {

	if (ShouldSelect) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector2D MouseLocation;

		if (PlayerController->GetMousePosition(MouseLocation.X, MouseLocation.Y)) {
			DrawRect(FLinearColor(0.8f, 0.1f, 0.0f, 0.2f), StartPosition.X, StartPosition.Y, MouseLocation.X - StartPosition.X, MouseLocation.Y - StartPosition.Y);
		}
	}
}

void AHUD_MouseSelection::SetSelectedQuad(const FInputActionValue& Value)
{
	ShouldSelect = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("HUD %s"), (Value.Get<bool>() ? TEXT("true") : TEXT("false")));

	if (ShouldSelect) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->GetMousePosition(StartPosition.X, StartPosition.Y);
	}
}

void AHUD_MouseSelection::BeginPlay() {

	Super::BeginPlay();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(GetOwningPlayerController()->InputComponent);

	if (InputActions) {
		Input->BindAction(InputActions->SelectQuad, ETriggerEvent::Triggered, this, &AHUD_MouseSelection::SetSelectedQuad);
	}
}
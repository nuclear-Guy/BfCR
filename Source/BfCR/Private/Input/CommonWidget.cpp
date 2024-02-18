// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CommonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/GamePlayerController.h"
#include "Input/HUD_MouseSelection.h"

void UCommonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// this works only for single player
	// 'verify' needs to avoid Engine crash
	verify((PlayerController = Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);

	if (AddUnitButton) {
		AddUnitButton->OnButtonClicked.AddDynamic(this, &UCommonWidget::OnButtonClicked);
	}

	if (SaveButton) {
		SaveButton->OnButtonClicked.AddDynamic(this, &UCommonWidget::OnButtonClicked);
	}

	if (WButton) {
		WButton->OnButtonClicked.AddDynamic(this, &UCommonWidget::OnButtonClicked);
	}

	if (AButton) {
		AButton->OnButtonClicked.AddDynamic(this, &UCommonWidget::OnButtonClicked);
	}
}

void UCommonWidget::OnButtonClicked(UButtonWidget* Button, TEnumAsByte<EButtons> ButtonType)
{
	if (PlayerController) {
		// reaction
		UE_LOG(LogTemp, Warning, TEXT("Player Controller react on button!!!"));
		AHUD_MouseSelection* HUD = Cast<AHUD_MouseSelection>(PlayerController->GetHUD());

		switch (ButtonType)
		{
		case EButtons::Line:
			HUD->BuildFormationLine();
			break;
		case EButtons::Rectangle:
			HUD->BuildFormationRectangle();
			break;
		default:
			break;
		}

	}
}

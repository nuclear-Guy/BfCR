// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Input/ButtonWidget.h"
#include "CommonWidget.generated.h"

class AGamePlayerController;

/**
 * 
 */
UCLASS()
class BFCR_API UCommonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButtonWidget* AddUnitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButtonWidget* SaveButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButtonWidget* WButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButtonWidget* AButton;

protected:
	UFUNCTION()
	void OnButtonClicked(UButtonWidget* Button, TEnumAsByte<EButtons> ButtonType);

	AGamePlayerController* PlayerController;
};

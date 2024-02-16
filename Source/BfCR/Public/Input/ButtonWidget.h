// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Input/UIButtonsData.h"
#include "ButtonWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class USimpleButtonWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonClicked, UButtonWidget*, Button, TEnumAsByte<EButtons>, ButtonType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonHovered, UButtonWidget*, Button, TEnumAsByte<EButtons>, ButtonType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonUnHovered, UButtonWidget*, Button, TEnumAsByte<EButtons>, ButtonType);

/**
 * 
 */
UCLASS()
class BFCR_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* Image;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonClicked OnButtonClicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonHovered OnButtonHovered;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonUnHovered OnButtonUnHovered;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	TEnumAsByte<EButtons> ButtonType;
	
protected:
	UFUNCTION()
	void OnSimpleUIButtonClickedEvent();

	UFUNCTION()
	void OnSimpleUIButtonHoveredEvent();

	UFUNCTION()
	void OnSimpleUIButtonUnHoveredEvent();
};

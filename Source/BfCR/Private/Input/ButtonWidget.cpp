// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddDynamic(this, &UButtonWidget::OnSimpleUIButtonClickedEvent);
	Button->OnHovered.AddDynamic(this, &UButtonWidget::OnSimpleUIButtonHoveredEvent);
	Button->OnUnhovered.AddDynamic(this, &UButtonWidget::OnSimpleUIButtonUnHoveredEvent);
}

void UButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Text) {
		Text->SetText(UEnum::GetDisplayValueAsText(ButtonType));
	}
}

void UButtonWidget::OnSimpleUIButtonClickedEvent()
{
	OnButtonClicked.Broadcast(this, ButtonType);
	UE_LOG(LogTemp, Warning, TEXT("You clicked!!!"));
}

void UButtonWidget::OnSimpleUIButtonHoveredEvent()
{
	OnButtonHovered.Broadcast(this, ButtonType);
}

void UButtonWidget::OnSimpleUIButtonUnHoveredEvent()
{
	OnButtonUnHovered.Broadcast(this, ButtonType);
}

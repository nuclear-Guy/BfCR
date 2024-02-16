// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIButtonsData.generated.h"

UENUM(BlueprintType)
enum EButtons {
	AddUnit UMETA(DisplayName = "Add Unit"),
	Save UMETA(DisplayName = "Save"),
	Line UMETA(DisplayName = "w"),
	Rectangle UMETA(DisplayName = "a")
};

/**
 * 
 */
UCLASS()
class BFCR_API UUIButtonsData : public UDataAsset
{
	GENERATED_BODY()
	
};

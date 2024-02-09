// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Input/InputDataConfig.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Unit/UnitParent.h"
#include "AIController.h"

#include "HUD_MouseSelection.generated.h"

/**
 * 
 */
UCLASS()
class BFCR_API AHUD_MouseSelection : public AHUD
{
	GENERATED_BODY()
	
protected:

    AHUD_MouseSelection();

    UInputDataConfig* InputActions;
    bool ShouldSelect = false;
    bool ShouldGetActors = false;
    FVector2D StartPosition;
    FVector2D StopPosition;
    TArray<AUnitParent*> ActorsInSelectionRect;

    //Draw HUD
    //void DrawHUD_Reset();
    virtual void DrawHUD() override;

    virtual void BeginPlay() override;

    void SetSelectedQuad(const FInputActionValue& Value);

public:
    bool GetLeaderPosition(FVector& Pos);
};

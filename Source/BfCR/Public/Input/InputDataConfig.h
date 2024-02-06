// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputDataConfig.generated.h"



UCLASS()
class BFCR_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* RotateCamera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ZoomCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* CameraFastMoving;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SelectQuad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveToTarget;
};

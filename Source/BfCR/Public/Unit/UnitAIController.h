// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

class AUnitParent;

/**
 * 
 */
UCLASS()
class BFCR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

	AUnitAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	AUnitParent* OwningCharacter;
};

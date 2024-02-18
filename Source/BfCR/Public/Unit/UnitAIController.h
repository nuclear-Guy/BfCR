// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/ObjectMacros.h"
#include "UnitAIController.generated.h"

class AUnitParent;

DECLARE_MULTICAST_DELEGATE_OneParam(FAIStatusChanged, EPathFollowingStatus::Type Status);

/**
 * 
 */
UCLASS()
class BFCR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

	AUnitAIController(FObjectInitializer const& ObjectInitializer/* = FObjectInitializer::Get()*/);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AUnitParent* OwningCharacter;

public:
	FAIStatusChanged OnAIStatusChanged;
	EPathFollowingStatus::Type Status;
};

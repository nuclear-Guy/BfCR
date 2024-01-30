// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitParent.h"
#include "Swordsman.generated.h"

/**
 * 
 */
UCLASS()
class BFCR_API ASwordsman : public AUnitParent
{
	GENERATED_BODY()

public:
	ASwordsman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

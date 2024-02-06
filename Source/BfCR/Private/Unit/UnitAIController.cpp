// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitAIController.h"
#include "Unit/UnitParent.h"

AUnitAIController::AUnitAIController(FObjectInitializer const& ObjectInitializer)
{
}

void AUnitAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningCharacter = Cast<AUnitParent>(InPawn);
	if (OwningCharacter) {
		OwningCharacter->SetAIController(this);
	}
}

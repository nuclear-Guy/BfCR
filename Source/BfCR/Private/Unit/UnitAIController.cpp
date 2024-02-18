// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitAIController.h"
#include "Unit/UnitParent.h"
#include "Navigation/CrowdFollowingComponent.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	//: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))) // to switch DetourCrowdAIController (works creepy)
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

void AUnitAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EPathFollowingStatus::Type PrevStatus = Status;
	Status = GetMoveStatus();

	if (PrevStatus != Status) {
		OnAIStatusChanged.Broadcast(Status);
	}
}



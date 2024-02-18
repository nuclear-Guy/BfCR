// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitParent.h"
#include "Unit/UnitAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

void AUnitParent::MoveToLocationTask(FVector Location)
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* PathData = NavSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), Location);

	if (PathData != NULL) {
		FAIMoveRequest Request;
		Request.SetAcceptanceRadius(0.5f);
		UnitAI->RequestMove(Request, PathData->GetPath());
	}
}

// Sets default values
AUnitParent::AUnitParent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Actions
	/*static ConstructorHelpers::FObjectFinder<UInputDataConfig> ContextFinder(TEXT("/Script/BfCR.InputDataConfig'/Game/Inputs/InputConfig.InputConfig'"));

	if (ContextFinder.Succeeded())
	{
		InputActions = ContextFinder.Object;
	}*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AUnitParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUnitParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

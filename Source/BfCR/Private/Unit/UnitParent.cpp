// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitParent.h"
#include "Unit/UnitAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
//#include "Components/SplineComponent.h"

void AUnitParent::MoveTask(const FInputActionValue& Value)
{
	if (Busy && Value.Get<bool>()) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FVector WorldDirection;
		FVector WorldLocation;
		if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
			FHitResult OutHit;

			if (GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, WorldLocation + (WorldDirection * 100000.f), ECollisionChannel::ECC_WorldStatic)) {
				if (OutHit.bBlockingHit) {
					UE_LOG(LogTemp, Warning, TEXT("Move: %f %f %f"), OutHit.Location.X, OutHit.Location.Y, OutHit.Location.Z);
					UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
					UNavigationPath* PathData = NavSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), OutHit.Location);

					//PathSpline->ClearSplinePoints();

					if (PathData != NULL) {
						FAIMoveRequest Request;
						Request.SetAcceptanceRadius(20.0f);
						UnitAI->RequestMove(Request, PathData->GetPath());

						/*PathSpline->SetSplinePoints(PathData->PathPoints, ESplineCoordinateSpace::World);

						int i = 0;
						for (FNavPathPoint Point : PathData->PathPoints) {
							FSplinePoint SplinePoint(i, Point, ESplinePointType::CurveClamped);
							PathSpline->AddPoint(SplinePoint, false);
							i++;
						}

						PathSpline->UpdateSpline();*/
					}
				}
			}

		}
	}
}

// Sets default values
AUnitParent::AUnitParent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Actions
	static ConstructorHelpers::FObjectFinder<UInputDataConfig> ContextFinder(TEXT("/Script/BfCR.InputDataConfig'/Game/Inputs/InputConfig.InputConfig'"));

	if (ContextFinder.Succeeded())
	{
		InputActions = ContextFinder.Object;
	}


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//PathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
}

// Called when the game starts or when spawned
void AUnitParent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

	if (InputActions) {
		Input->BindAction(InputActions->MoveToTarget, ETriggerEvent::Triggered, this, &AUnitParent::MoveTask);
	}
}

// Called every frame
void AUnitParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitParent::SetStatusBusy(bool status)
{
	Busy = status;
}

bool AUnitParent::IsBusy()
{
	return Busy;
}

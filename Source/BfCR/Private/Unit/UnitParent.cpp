// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitParent.h"
#include "Unit/UnitAIController.h"
#include "Kismet/GameplayStatics.h"

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
					UnitAI->MoveToLocation(OutHit.Location, 20.f);
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

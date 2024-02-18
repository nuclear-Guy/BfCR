// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HUD_MouseSelection.h"
#include "Kismet/GameplayStatics.h"
#include "Unit/UnitAIController.h"
#include "Navigation/PathFollowingComponent.h"

AHUD_MouseSelection::AHUD_MouseSelection() {
	static ConstructorHelpers::FObjectFinder<UInputDataConfig> ContextFinderConfig(TEXT("/Script/BfCR.InputDataConfig'/Game/Inputs/InputConfig.InputConfig'"));
	if (ContextFinderConfig.Succeeded())
	{
		InputActions = ContextFinderConfig.Object;
	}
}

void AHUD_MouseSelection::DrawHUD() {

	if (ShouldSelect) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector2D MouseLocation;

		if (PlayerController->GetMousePosition(MouseLocation.X, MouseLocation.Y)) {
			DrawRect(FLinearColor(0.8f, 0.1f, 0.0f, 0.2f), StartPosition.X, StartPosition.Y, MouseLocation.X - StartPosition.X, MouseLocation.Y - StartPosition.Y);
			StopPosition = MouseLocation;
		}
	}

	if (ShouldGetActors) {
		for (AUnitParent*& Actor : ActorsInSelectionRect)
		{
			Actor->GetMesh()->SetRenderCustomDepth(false);
		}

		ActorsInSelectionRect.Empty();

		// TODO custom function
		GetActorsInSelectionRectangle(StartPosition, StopPosition, ActorsInSelectionRect, false, false);
		for (AUnitParent*& Actor : ActorsInSelectionRect)
		{
			Actor->GetMesh()->SetRenderCustomDepth(true);
			Actor->GetMesh()->SetCustomDepthStencilValue(1);
		}

		UE_LOG(LogTemp, Warning, TEXT("Count %d %f %f"), ActorsInSelectionRect.Num(), StartPosition.X - StopPosition.X, StartPosition.Y - StopPosition.Y);

		ShouldGetActors = false;
	}
}

void AHUD_MouseSelection::SetSelectedQuad(const FInputActionValue& Value)
{
	ShouldGetActors = !Value.Get<bool>() && ShouldSelect;
	ShouldSelect = Value.Get<bool>();

	if (ShouldSelect) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->GetMousePosition(StartPosition.X, StartPosition.Y);
	}
}

void AHUD_MouseSelection::SquadMoveTo(const FInputActionValue& Value)
{
	if (Value.Get<bool>()) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FVector WorldDirection;
		FVector WorldLocation;
		if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
			FHitResult OutHit;

			if (GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, WorldLocation + (WorldDirection * 100000.f), ECollisionChannel::ECC_WorldStatic)) {
				if (OutHit.bBlockingHit) {
					UE_LOG(LogTemp, Warning, TEXT("Move: %f %f %f"), OutHit.Location.X, OutHit.Location.Y, OutHit.Location.Z);

					if (ActorsInSelectionRect.Num() > 0) {
						AUnitParent* Leader = ActorsInSelectionRect[0];
						FVector LeaderPosition = Leader->GetActorLocation();

						FVector MoveVector = OutHit.Location - LeaderPosition;
						MoveVector.Normalize();

						double Distance = FVector::Distance(OutHit.Location, LeaderPosition);
						for (AUnitParent*& Actor : ActorsInSelectionRect)
						{
							FVector Position = Actor->GetActorLocation() + Distance * MoveVector;
							Actor->MoveToLocationTask(Position);
						}
					}
				}
			}

		}
	}
}

bool AHUD_MouseSelection::GetLeaderPosition(FVector& Pos)
{

	for (AUnitParent*& Actor : ActorsInSelectionRect) {
		Pos = Actor->GetActorLocation();
		return true;
	}

	return false;
}

void AHUD_MouseSelection::BuildFormationLine()
{
	float FormationSpacing = 150.0f;

	if (ActorsInSelectionRect.Num() > 0) {
		AUnitParent* Leader = ActorsInSelectionRect[0];
		FVector LeaderLocation = Leader->GetActorLocation();
		FRotator LeaderRotation = Leader->GetActorRotation();

		for (int i = 1; i < ActorsInSelectionRect.Num(); i++) {
			AUnitParent* Next = ActorsInSelectionRect[i];

			FVector Offset = FVector(0.0f, 1.0f, 0.0f) * FormationSpacing * i;
			Offset = LeaderRotation.RotateVector(Offset);

			FVector Position = Offset + LeaderLocation;
			Next->MoveToLocationTask(Position);

			Next->GetAIController()->OnAIStatusChanged.AddLambda([](EPathFollowingStatus::Type Status, AUnitParent* Next, FRotator Rotator)
				{
					UE_LOG(LogTemp, Warning, TEXT("Line Status %d"), Status);
					if (Status == 0) {
						Next->SetActorRotation(Rotator);
						Next->GetAIController()->OnAIStatusChanged.Clear();
					}
				}, Next, LeaderRotation);
		}
	}
}

void AHUD_MouseSelection::BuildFormationRectangle()
{
	float FormationSpacing = 150.0f;
	uint8 NumInLine = 3;

	if (ActorsInSelectionRect.Num() > 0) {
		AUnitParent* Leader = ActorsInSelectionRect[0];
		FVector LeaderLocation = Leader->GetActorLocation();
		FRotator LeaderRotation = Leader->GetActorRotation();

		for (int i = 1; i < ActorsInSelectionRect.Num(); i++) {
			AUnitParent* Next = ActorsInSelectionRect[i];

			FVector Offset = FVector(-FormationSpacing * (i / 3), FormationSpacing * (i % 3), 0.0f);
			Offset = LeaderRotation.RotateVector(Offset);

			FVector Position = Offset + LeaderLocation;
			Next->MoveToLocationTask(Position);

			Next->GetAIController()->OnAIStatusChanged.AddLambda([](EPathFollowingStatus::Type Status, AUnitParent* Next, FRotator Rotator)
				{
					UE_LOG(LogTemp, Warning, TEXT("Rectangle Status %d"), Status);
					if (Status == 0) {
						Next->SetActorRotation(Rotator);
						Next->GetAIController()->OnAIStatusChanged.Clear();
					}
				}, Next, LeaderRotation);
		}
	}
}

void AHUD_MouseSelection::BeginPlay() {

	Super::BeginPlay();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(GetOwningPlayerController()->InputComponent);

	if (InputActions) {
		Input->BindAction(InputActions->SelectQuad, ETriggerEvent::Triggered, this, &AHUD_MouseSelection::SetSelectedQuad);
		Input->BindAction(InputActions->MoveToTarget, ETriggerEvent::Triggered, this, &AHUD_MouseSelection::SquadMoveTo);
	}
}
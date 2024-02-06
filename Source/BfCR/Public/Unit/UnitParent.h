// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Input/InputDataConfig.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UnitParent.generated.h"

class AUnitAIController;

UCLASS()
class BFCR_API AUnitParent : public ACharacter
{
	GENERATED_BODY()

	bool Busy = false;
	UInputDataConfig* InputActions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AUnitAIController* UnitAI;

	UFUNCTION()
	void MoveTask(const FInputActionValue& Value);

public:	
	// Sets default values for this character's properties
	AUnitParent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStatusBusy(bool status);
	bool IsBusy();

	UFUNCTION()
	void SetAIController(AUnitAIController* NewAIController) { UnitAI = NewAIController; }
};

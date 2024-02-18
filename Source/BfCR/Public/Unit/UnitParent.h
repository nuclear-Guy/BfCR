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

	UInputDataConfig* InputActions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AUnitAIController* UnitAI;

public:	
	// Sets default values for this character's properties
	AUnitParent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetAIController(AUnitAIController* NewAIController) { UnitAI = NewAIController; }

	UFUNCTION()
	AUnitAIController* GetAIController() { return UnitAI; }

	UFUNCTION()
	void MoveToLocationTask(FVector Location);
};

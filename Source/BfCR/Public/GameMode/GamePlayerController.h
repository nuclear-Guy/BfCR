#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Input/InputDataConfig.h"
#include "Engine/DataTable.h"
#include "GamePlayerController.generated.h"


/**
 *
 */
UCLASS()
class BFCR_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	AGamePlayerController();

public:

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetBPClass;

	UFUNCTION()
	void AddGroupOfUnits();

	UFUNCTION()
	void SaveGame();

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InputMappingContext.h"
#include "Input/InputDataConfig.h"
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

};

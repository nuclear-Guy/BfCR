#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Input/InputDataConfig.h"
#include "CameraSetup.generated.h"

class UInputMappingContext;

UCLASS()
class BFCR_API ACameraSetup : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraSetup();

protected:
	UPROPERTY(EditAnywhere)
	float CameraSpeed = 800.0f;

	UPROPERTY(EditAnywhere)
	float FastCameraSpeed = 1400.0f;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	float SpringArmDefaultLength = 1200.0f;

	UPROPERTY(EditAnywhere)
	float SpringArmMaxLength = 3000.0f;

	UPROPERTY(EditAnywhere)
	float SpringArmMinLength = 200.0f;

	UPROPERTY(EditAnywhere)
	float CameraZoomPerUnit = 20.0f;

	// Invisible in editor
	bool ShouldRotateCamera = false;
	FVector2D MouseLocation;
	float ShouldZoom = 0.0f;
	bool FastMoving = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;


	/** MappingContext for player input. */
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputDataConfig* InputActions;

	UFUNCTION()
	void RotateCamera(const FInputActionValue& Value);

	UFUNCTION()
	void ZoomCamera(const FInputActionValue& Value);

	UFUNCTION()
	void SwitchFastMode(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

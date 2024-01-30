#include "Camera/CameraSetup.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraSetup::ACameraSetup()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Attach our components RootComponent->StaticMeshComp->SpringArmComp->CameraComp
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//Assign SpringArm class variables.
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = SpringArmDefaultLength;
	SpringArmComp->bEnableCameraLag = true; // smooth movement
	SpringArmComp->CameraLagSpeed = 3.0f;

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACameraSetup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraSetup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D ViewPortSize;
	GEngine->GameViewport->GetViewportSize(ViewPortSize);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector2D PrevMouseLocation = MouseLocation;

	if (PlayerController->GetMousePosition(MouseLocation.X, MouseLocation.Y)) {

		// Move by Mouse
		{
			if (!FastMoving) {
				FVector2D MovementInput;
				FVector2D Percentage = MouseLocation / ViewPortSize;

				if (Percentage.X <= 0.02) {
					MovementInput.Y = -1;
				}
				else if (Percentage.X >= 0.98) {
					MovementInput.Y = 1;
				}
				else {
					MovementInput.Y = 0;
				}

				if (Percentage.Y <= 0.02) {
					MovementInput.X = 1;
				}
				else if (Percentage.Y >= 0.98) {
					MovementInput.X = -1;
				}
				else {
					MovementInput.X = 0;
				}

				if (!MovementInput.IsZero())
				{

					FVector Location = GetActorLocation();
					// Update the left/right movement based on the direction to the right of where we are facing
					Location += SpringArmComp->GetRightVector() * CameraSpeed * MovementInput.Y * DeltaTime;

					// Update the forward/backwards movement based on the yaw rotation, **ignoring pitch** so the camera remains level as it moves (looking down would otherwise pan the camera forward and down)
					Location += FRotationMatrix(FRotator(0, SpringArmComp->GetRelativeRotation().Yaw, 0)).GetScaledAxis(EAxis::X) * CameraSpeed * MovementInput.X * DeltaTime;

					SetActorLocation(Location);
				}
			}
			else {
				FVector2D ScreenCenter(ViewPortSize.X / 2, ViewPortSize.Y / 2);
				FVector2D Direction(MouseLocation.X - ScreenCenter.X, ScreenCenter.Y - MouseLocation.Y);
				Direction = Direction.GetSafeNormal();

				UE_LOG(LogTemp, Warning, TEXT("Direction: %f %f"), Direction.X, Direction.Y);

				FVector Location = GetActorLocation();
				// Update the left/right movement based on the direction to the right of where we are facing
				Location += SpringArmComp->GetRightVector() * FastCameraSpeed * Direction.X * DeltaTime;

				// Update the forward/backwards movement based on the yaw rotation, **ignoring pitch** so the camera remains level as it moves (looking down would otherwise pan the camera forward and down)
				Location += FRotationMatrix(FRotator(0, SpringArmComp->GetRelativeRotation().Yaw, 0)).GetScaledAxis(EAxis::X) * FastCameraSpeed * Direction.Y * DeltaTime;

				SetActorLocation(Location);
			}
		}

		// Rotate Camera
		{
			if (ShouldRotateCamera) {
				// Get how much we have moved since the last frame/rotate start
				const float XPercent = (MouseLocation.X - PrevMouseLocation.X) / ViewPortSize.X;
				const float YPercent = (PrevMouseLocation.Y - MouseLocation.Y) / ViewPortSize.Y;

				// Get the current rotation within -180 to 180 degrees, instead of 0-360
				const FRotator CurrentRot = SpringArmComp->GetRelativeRotation().GetNormalized();

				// Update our rotation based on 100% movement equals 180 degrees rotation, limiting pitch to near vertical to limit issues at -90 and 90 degrees
				SpringArmComp->SetRelativeRotation(FRotator(FMath::Clamp<float>(CurrentRot.Pitch + (YPercent * 180), -88, 88)/*CurrentRot.Pitch*/,
					CurrentRot.Yaw + (XPercent * 180), 0));
			}
		}

		// Zoom Camera 
		{
			if (!FMath::IsNearlyZero(ShouldZoom)) {
				// This allows us to smoothly zoom to our desired target arm length over time
				SpringArmComp->TargetArmLength = FMath::FInterpTo(SpringArmComp->TargetArmLength, ShouldZoom, DeltaTime, ZoomSpeed);
			}
		}
	}
}

void ACameraSetup::RotateCamera(const FInputActionValue& Value) 
{
	ShouldRotateCamera = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (ShouldRotateCamera ? TEXT("true") : TEXT("false")));
}

void ACameraSetup::ZoomCamera(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), FloatValue);

	float ZoomAmount;

	if (FloatValue > 0) {
		ZoomAmount = -CameraZoomPerUnit;
	}
	else {
		ZoomAmount = CameraZoomPerUnit;
	}

	// Update the target distance within our bounds
	ShouldZoom = FMath::Clamp(SpringArmComp->TargetArmLength + ZoomAmount, SpringArmMinLength, SpringArmMaxLength);
}

void ACameraSetup::SwitchFastMode(const FInputActionValue& Value) {
	FastMoving = Value.Get<bool>();
}

// Called to bind functionality to input
void ACameraSetup::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (InputActions) {
		Input->BindAction(InputActions->RotateCamera, ETriggerEvent::Triggered, this, &ACameraSetup::RotateCamera);
		Input->BindAction(InputActions->ZoomCamera, ETriggerEvent::Triggered, this, &ACameraSetup::ZoomCamera);
		Input->BindAction(InputActions->CameraFastMoving, ETriggerEvent::Triggered, this, &ACameraSetup::SwitchFastMode);
	}
}


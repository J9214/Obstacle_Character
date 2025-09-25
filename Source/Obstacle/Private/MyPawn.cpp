#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPlayerController.h"
#include "Camera/CameraComponent.h"
// Sets default values
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	MovementComp->MaxSpeed = NormalSpeed;

	MouseSensitivity = 120.f;
	MaxPitch = 20.0f;
	MinPitch = -80.0f;
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::StartSprint
				);
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AMyPawn::StopSprint
				);
			}
		}
	}
	
}

void AMyPawn::Move(const FInputActionValue& value)
{
	if (!Controller)return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	const float DT = GetWorld()->GetDeltaSeconds();

	float XSpeed = MoveInput.X * MovementComp->MaxSpeed * DT;
	float YSpeed = MoveInput.Y * MovementComp->MaxSpeed * DT;

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector Offset = FVector(XSpeed, 0.0f, 0.0f);
		AddActorLocalOffset(Offset);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector Offset = FVector(0.0f, YSpeed, 0.0f);
		AddActorLocalOffset(Offset);
	}
}

void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	const float DT = GetWorld()->GetDeltaSeconds();
	
	AddActorLocalRotation(FRotator(0.f, LookInput.X * MouseSensitivity * DT, 0.f), false);

	FRotator CamR = SpringArmComp->GetRelativeRotation();
	CamR.Pitch = FMath::Clamp(CamR.Pitch + LookInput.Y * MouseSensitivity * DT * -1, MinPitch, MaxPitch);
	SpringArmComp->SetRelativeRotation(CamR);
}

 void AMyPawn::StartSprint(const FInputActionValue& value)
{
	 MovementComp->MaxSpeed = SprintSpeed;
}

void AMyPawn::StopSprint(const FInputActionValue& value)
{
	MovementComp->MaxSpeed = NormalSpeed;
}

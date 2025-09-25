// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObstacle.h"

// Sets default values
AMyObstacle::AMyObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = 1.0f;
	MaxRange = FVector(0.0f, 0.0f, 0.0f);
	RotationSpeed = FVector(0.0f, 0.0f, 0.0f);

}

// Called when the game starts or when spawned
void AMyObstacle::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	EndLocation = StartLocation + MaxRange;
}

// Called every frame
void AMyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Time = GetWorld()->GetTimeSeconds();
	float LerpAlpha = FMath::Sin(Time * Velocity);

	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, (LerpAlpha + 1) / 2);
	SetActorLocation(NewLocation); 

	FRotator NewRotation = FRotator(RotationSpeed.X * DeltaTime, RotationSpeed.Y * DeltaTime, RotationSpeed.Z * DeltaTime);
	AddActorLocalRotation(NewRotation);
}


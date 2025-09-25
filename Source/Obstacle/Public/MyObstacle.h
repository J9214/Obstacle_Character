// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyObstacle.generated.h"

UCLASS()
class OBSTACLE_API AMyObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform Setting")
	FVector StartLocation;
	FVector EndLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform Setting")
	FVector RotationSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform Setting")
	float Velocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform Setting")
	FVector MaxRange;
};

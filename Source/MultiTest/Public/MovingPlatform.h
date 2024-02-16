// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */

class UBoxComponent;
UCLASS()
class MULTITEST_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	//is relative location
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	
	UPROPERTY()
	UBoxComponent* MainCollider;

	UPROPERTY(EditAnywhere)
	FVector PlatformSize = FVector(1,1,1);
	
	FVector GlobalStartLocation;
	FVector GlobalEndLocation;

	FVector MoveDirection;

	float TargetTravelDistance;

};

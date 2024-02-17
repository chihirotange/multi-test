// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Interface/Activatable.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */

class UBoxComponent;
UCLASS()
class MULTITEST_API AMovingPlatform : public AStaticMeshActor, public IActivatable
{
	GENERATED_BODY()

public:
	virtual bool Activate_Implementation() override;
	virtual bool Deactivate_Implementation() override;
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
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* MainCollider;

	UPROPERTY(EditAnywhere)
	FVector PlatformSize = FVector(1,1,1);

	UPROPERTY(EditAnywhere)
	bool StartActivated = true;
	
	FVector GlobalStartLocation;
	FVector GlobalEndLocation;

	FVector MoveDirection;

	float TargetTravelDistance;

};

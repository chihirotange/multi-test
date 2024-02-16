// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Components/BoxComponent.h"

AMovingPlatform::AMovingPlatform()
{
	MainCollider = CreateDefaultSubobject<UBoxComponent>("Main Collider");
	RootComponent = MainCollider;
	GetStaticMeshComponent()->SetCollisionProfileName(FName("NoCollision"));
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalEndLocation = GetTransform().TransformPosition(TargetLocation);
	TargetTravelDistance = TargetLocation.Size();
	MoveDirection = (GlobalEndLocation - GlobalStartLocation).GetSafeNormal();
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Location = GetActorLocation();
	float JourneyLength = FVector::Distance(Location, GlobalStartLocation);

	if (JourneyLength >= TargetTravelDistance)
	{
		FVector Swap = GlobalStartLocation;
		GlobalStartLocation = GlobalEndLocation;
		GlobalEndLocation = Swap;
		MoveDirection = (GlobalEndLocation - GlobalStartLocation).GetSafeNormal();
	}
	
	Location += MoveDirection * MoveSpeed * DeltaSeconds;

	SetActorLocation(Location);
}

void AMovingPlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!IsValid(MainCollider))
	{
		return;
	}
	MainCollider->SetBoxExtent(PlatformSize/2);
}

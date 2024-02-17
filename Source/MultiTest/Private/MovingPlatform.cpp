// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "ShaderPrintParameters.h"
#include "Components/BoxComponent.h"

bool AMovingPlatform::Activate_Implementation()
{
	SetActorTickEnabled(true);
	return true;
}

bool AMovingPlatform::Deactivate_Implementation()
{
	SetActorTickEnabled(false);
	return true;
}

AMovingPlatform::AMovingPlatform()
{
	MainCollider = CreateDefaultSubobject<UBoxComponent>("Main Collider");
	SetRootComponent(MainCollider);
	GetStaticMeshComponent()->SetCollisionProfileName(FName("NoCollision"));
	MainCollider->SetCollisionProfileName(FName("BlockAll"));
	SetMobility(EComponentMobility::Movable);

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);

	if(StartActivated)
	{
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorTickEnabled(false);
	}
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
	if (!IsValid(MainCollider) || !IsValid(GetStaticMeshComponent()))
	{
		return;
	}
	MainCollider->SetBoxExtent(PlatformSize/2);

	//prevent this component not moving when moving the actor (stuck to (0,0,0))
	GetStaticMeshComponent()->SetupAttachment(MainCollider);
}

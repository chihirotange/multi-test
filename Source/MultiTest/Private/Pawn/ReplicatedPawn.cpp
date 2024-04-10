// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "Pawn/ReplicatedPawn.h"

// Sets default values
AReplicatedPawn::AReplicatedPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(false);
	NetUpdateFrequency = 5;
	MinNetUpdateFrequency = 1;
}

// Called when the game starts or when spawned
void AReplicatedPawn::BeginPlay()
{
	Super::BeginPlay();
	ReplicatedTransform = GetActorTransform();
}

// Called every frame
void AReplicatedPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), ReplicatedTransform.GetLocation(), DeltaTime, 10));
}

void AReplicatedPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReplicatedPawn, ReplicatedTransform);
}

// Called to bind functionality to input
void AReplicatedPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AReplicatedPawn::MoveForward()
{
	ReplicatedTransform.AddToTranslation(FVector(1, 0, 0) * MoveSpeed);
	Server_MoveForward();
}

void AReplicatedPawn::Server_MoveForward_Implementation()
{
	ReplicatedTransform.AddToTranslation(FVector(1, 0, 0) * MoveSpeed);
	SetRepProperties();
}

void AReplicatedPawn::MoveBackward()
{
	ReplicatedTransform.AddToTranslation(FVector(-1, 0, 0) * MoveSpeed);
	Server_MoveBackward();
}

void AReplicatedPawn::Server_MoveBackward_Implementation()
{
	ReplicatedTransform.AddToTranslation(FVector(-1, 0, 0) * MoveSpeed);
	SetRepProperties();
}

void AReplicatedPawn::SetRepProperties()
{
	// ReplicatedTransform = GetActorTransform();
}

void AReplicatedPawn::OnRep_ReplicatedTransform()
{
	// SetActorTransform(ReplicatedTransform);
}


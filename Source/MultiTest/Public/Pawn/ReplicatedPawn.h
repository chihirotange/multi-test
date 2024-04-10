// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ReplicatedPawn.generated.h"

UCLASS()
class MULTITEST_API AReplicatedPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AReplicatedPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveForward();

	UFUNCTION(BlueprintCallable)
	void MoveBackward();

	UFUNCTION(Server, Reliable)
	void Server_MoveBackward();

	UFUNCTION(Server, Reliable)
	void Server_MoveForward();

	void SetRepProperties();
private:
	//trigger on client only (different than blueprint)
	UFUNCTION()
	void OnRep_ReplicatedTransform();

private:
	UPROPERTY(ReplicatedUsing=OnRep_ReplicatedTransform)
	FTransform ReplicatedTransform;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTITEST_API AMultiTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void Join(const FString& IP);
};

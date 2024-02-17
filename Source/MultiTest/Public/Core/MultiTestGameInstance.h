// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiTestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTITEST_API UMultiTestGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& IP);
};

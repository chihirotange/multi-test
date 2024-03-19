// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MULTITEST_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Host();
	virtual void Host_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Join(const FString& IP);
	virtual void Join_Implementation(const FString& IP) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Find();
	virtual void Find_Implementation() = 0;
};

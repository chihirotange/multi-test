// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/GenericMenuUI.h"
#include "MultiTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTITEST_API AMultiTestPlayerController : public APlayerController, public IGenericMenuUI
{
public:
	virtual bool LoadMainMenu_Implementation() override;

private:
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void Join(const FString& IP);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};

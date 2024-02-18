// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/GenericMenuUI.h"
#include "UI/Interface/MenuInterface.h"
#include "MultiTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTITEST_API AMultiTestPlayerController : public APlayerController, public IGenericMenuUI, public IMenuInterface
{
public:
	virtual void Host_Implementation() override;
	virtual void Join_Implementation(const FString& IP) override;

	virtual bool LoadMainMenu_Implementation() override;

private:
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};

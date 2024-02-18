// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/GenericMenuUI.h"
#include "MultiTestGameInstance.generated.h"

/**
 * 
 */
class APlayerController;
class UUserWidget;
UCLASS()
class MULTITEST_API UMultiTestGameInstance : public UGameInstance
{
private:
	GENERATED_BODY()

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();
private:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	APlayerController* CurrentLocalPlayerController;
};
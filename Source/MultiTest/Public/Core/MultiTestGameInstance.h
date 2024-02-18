// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/GenericMenuUI.h"
#include "MultiTestGameInstance.generated.h"

/**
 * 
 */

class UUserWidget;
UCLASS()
class MULTITEST_API UMultiTestGameInstance : public UGameInstance, public IGenericMenuUI
{
public:
	virtual bool LoadMainMenu_Implementation() override;

private:
	GENERATED_BODY()

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& IP);

private:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
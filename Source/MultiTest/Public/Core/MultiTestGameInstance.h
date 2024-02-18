// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/Interface/MenuInterface.h"
#include "MultiTestGameInstance.generated.h"

/**
 * 
 */
class APlayerController;
class UUserWidget;
UCLASS()
class MULTITEST_API UMultiTestGameInstance : public UGameInstance, public IMenuInterface
{
public:
	virtual void Join_Implementation(const FString& IP) override;

	virtual void Host_Implementation() override;

private:
	GENERATED_BODY()

	virtual void Init() override;

private:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
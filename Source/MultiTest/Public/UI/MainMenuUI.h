// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS(Abstract)
class MULTITEST_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Host;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Join;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* IpAddress;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

private:
	UPROPERTY()
	UGameInstance* CurrentGameInstance;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MultiTestPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "UI/MainMenuUI.h"

void AMultiTestPlayerController::Host_Implementation()
{
}

void AMultiTestPlayerController::Join_Implementation(const FString& IP)
{
	ClientTravel(IP, TRAVEL_Absolute);
}

bool AMultiTestPlayerController::LoadMainMenu_Implementation()
{
	if(!IsValid(MainMenuWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Main menu widget not assigned in player controller!"));
		return false;
	}
	UUserWidget* MainMenuWidget = CreateWidget(this, MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
	
	FInputModeUIOnly InputData;
	// InputData.SetWidgetToFocus(MainMenuWidget->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	bShowMouseCursor = true;
	return true;
}

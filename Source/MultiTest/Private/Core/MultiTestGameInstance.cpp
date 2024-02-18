// Fill out your copyright notice in the Description page of Project Settings.
#include "Core/MultiTestGameInstance.h"
#include "Blueprint/UserWidget.h"

bool UMultiTestGameInstance::LoadMainMenu_Implementation()
{
	if(!IsValid(MainMenuWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("No assigned main menu widget class in game instance!"));
		return false;
	}
	UUserWidget* MainMenu = CreateWidget(this, MainMenuWidgetClass);
	MainMenu->AddToViewport();
	return true;
}

void UMultiTestGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init"));
}

void UMultiTestGameInstance::Host()
{
	UWorld* CurrentWorld = GetWorld();
	if(!IsValid(CurrentWorld))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot get current world"));
		return;
	}
	//?listen for other to join
	CurrentWorld->ServerTravel("/Game/Levels/L_Playground?listen");
}

void UMultiTestGameInstance::Join(const FString& IP)
{
	APlayerController* LocalPlayerController = GetFirstLocalPlayerController();
	if (!IsValid(LocalPlayerController))
	{
		return;
	}
	LocalPlayerController->ClientTravel(IP, TRAVEL_Absolute);
}

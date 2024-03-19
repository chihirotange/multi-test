// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MultiTestPlayerController.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UI/MainMenuUI.h"

void AMultiTestPlayerController::Find_Implementation()
{
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		OnlineSession->FindSessions(0, SessionSearch.ToSharedRef());
		OnlineSession->OnFindSessionsCompleteDelegates.AddUObject(this, &AMultiTestPlayerController::OnFindSessionComplete);
	}
}

void AMultiTestPlayerController::Host_Implementation()
{
}

void AMultiTestPlayerController::Join_Implementation(const FString& IP)
{
	OnlineSession->JoinSession(0,"Ai chan", CurrentSessionSearchResult);
	OnlineSession->OnJoinSessionCompleteDelegates.AddUObject(this, &AMultiTestPlayerController::OnJoinSessionComplete);

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

void AMultiTestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem == nullptr)
	{
		return;
	}
	OnlineSession = OnlineSubsystem->GetSessionInterface();

	SessionSearch = MakeShareable(new FOnlineSessionSearch());

}

void AMultiTestPlayerController::OnFindSessionComplete(bool Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Find session completed"));
	for (auto& SearchResult : SessionSearch->SearchResults)
	{
		CurrentSessionSearchResult = SearchResult;
	}
}

void AMultiTestPlayerController::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Type)
{
	UE_LOG(LogTemp, Warning, TEXT("join session compolete"));
	FString ConnectString;
	OnlineSession->GetResolvedConnectString(SessionName, ConnectString);
	ClientTravel(ConnectString, TRAVEL_Absolute);
}

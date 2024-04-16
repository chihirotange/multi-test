// Fill out your copyright notice in the Description page of Project Settings.
#include "Core/MultiTestGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UMultiTestGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem == nullptr) return;
	FName Name = OnlineSubsystem->GetSubsystemName();
	UE_LOG(LogTemp, Warning, TEXT("Created subsystem name %s"), *Name.ToString());

	CurrentOnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!ensure(CurrentOnlineSessionInterface.IsValid())) {}
}

void UMultiTestGameInstance::OnCreateSessionCompleted(FName Name, bool Success) const
{
	if(!Success) return;
	CurrentOnlineSessionInterface->OnCreateSessionCompleteDelegates.Remove(CreateSessionDelegateHandle);
	UE_LOG(LogTemp, Log, TEXT("Created session %s"), *Name.ToString());
	UWorld* CurrentWorld = GetWorld();
	if(!ensure(IsValid(CurrentWorld)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot get current world"));
		return;
	}
	CurrentWorld->ServerTravel("/Game/Levels/L_Playground?listen");
}

void UMultiTestGameInstance::OnCreateSessionAfterSessionDestroy(FName Name, bool Success)
{
	if(!Success) return;
	CurrentOnlineSessionInterface->OnDestroySessionCompleteDelegates.Remove(DestroySessionDelegateHandle);
	CreateOnlineSession(Name);
}

bool UMultiTestGameInstance::IsSessionExists(const FName& SessionName, FNamedOnlineSession*& Session)
{
	Session = CurrentOnlineSessionInterface->GetNamedSession(SessionName);
	return(Session != nullptr);
}

void UMultiTestGameInstance::Find_Implementation()
{
}

void UMultiTestGameInstance::Join_Implementation(const FString& IP)
{
}

void UMultiTestGameInstance::Host_Implementation()
{
	FNamedOnlineSession* FoundSession;
	if(IsSessionExists("Ai chan", FoundSession))
	{
		DestroySessionDelegateHandle = CurrentOnlineSessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiTestGameInstance::OnCreateSessionAfterSessionDestroy);
		CurrentOnlineSessionInterface->DestroySession("Ai chan");
		return;
	}
	CreateOnlineSession("Ai chan");
}

bool UMultiTestGameInstance::CreateOnlineSession(const FName& SessionName)
{
	CreateSessionDelegateHandle = CurrentOnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiTestGameInstance::OnCreateSessionCompleted);
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 2;
	CurrentOnlineSessionInterface->CreateSession(0, SessionName, SessionSettings);
	return true;
}
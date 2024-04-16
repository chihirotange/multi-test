// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Engine/GameInstance.h"
#include "UI/Interface/MenuInterface.h"
#include "MultiTestGameInstance.generated.h"

class UMainMenuUI;
class FNamedOnlineSession;
class IOnlineSubsystem;
/**
 * 
 */
class APlayerController;
class UUserWidget;
UCLASS()
class MULTITEST_API UMultiTestGameInstance : public UGameInstance, public IMenuInterface
{
public:
	virtual void Find_Implementation() override;

	virtual void Join_Implementation(const FString& IP) override;

	virtual void Host_Implementation() override;

private:
	GENERATED_BODY()

	virtual void Init() override;
	
	UFUNCTION()
	void OnCreateSessionCompleted(FName Name, bool Success) const;

	UFUNCTION()
	void OnCreateSessionAfterSessionDestroy(FName Name, bool Success);

	bool IsSessionExists(const FName& SessionName, FNamedOnlineSession*& Session);
	bool CreateOnlineSession(const FName& SessionName);

private:

	IOnlineSessionPtr CurrentOnlineSessionInterface;
	FDelegateHandle DestroySessionDelegateHandle;
	FDelegateHandle CreateSessionDelegateHandle;
};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/PlayerController.h"
#include "Interface/GenericMenuUI.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UI/Interface/MenuInterface.h"
#include "MultiTestPlayerController.generated.h"

class UMainMenuUI;
/**
 * 
 */
UCLASS()
class MULTITEST_API AMultiTestPlayerController : public APlayerController, public IGenericMenuUI, public IMenuInterface
{
public:
	virtual void Find_Implementation() override;

	virtual void Host_Implementation() override;
	virtual void Join_Implementation(const FString& IP) override;

	virtual bool LoadMainMenu_Implementation() override;

private:
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuUI> MainMenuWidgetClass;

	IOnlineSessionPtr OnlineSession;
	FOnlineSessionSearchResult CurrentSessionSearchResult;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

private:
	UFUNCTION()
	void OnFindSessionComplete(bool Result);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Type);
};

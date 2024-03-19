// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI/Interface/MenuInterface.h"

bool UMainMenuUI::Initialize()
{
	if(!Super::Initialize()) return false;

	if(!IsValid(Host) || !IsValid(Join)) return false;

	CurrentGameInstance = GetGameInstance();
	OwningPlayerController = GetOwningPlayer();

	if(!IsValid(CurrentGameInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get game instance"));
		return false;
	}
	Host->OnClicked.AddDynamic(this, &UMainMenuUI::HostServer);
	Join->OnClicked.AddDynamic(this, &UMainMenuUI::JoinServer);
	Find->OnClicked.AddDynamic(this, &UMainMenuUI::FindServer);

	if(!CurrentGameInstance->Implements<UMenuInterface>() || !OwningPlayerController->Implements<UMenuInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("Make sure game instance and player controller implemented IMenuInterface"));
		return false;
	}

	return true;
}

void UMainMenuUI::HostServer()
{
	IMenuInterface::Execute_Host(CurrentGameInstance);
}

void UMainMenuUI::JoinServer()
{
	if(!IsValid(IpAddress)) return;
	IMenuInterface::Execute_Join(OwningPlayerController, IpAddress->GetText().ToString());
}

void UMainMenuUI::FindServer()
{
	UE_LOG(LogTemp, Error, TEXT("Find server"));
	IMenuInterface::Execute_Find(OwningPlayerController);
}

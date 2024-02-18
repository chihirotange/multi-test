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

	if(!IsValid(CurrentGameInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get game instance"));
		return false;
	}
	Host->OnClicked.AddDynamic(this, &UMainMenuUI::HostServer);
	Join->OnClicked.AddDynamic(this, &UMainMenuUI::JoinServer);

	return true;
}

void UMainMenuUI::HostServer()
{
	if(!CurrentGameInstance->Implements<UMenuInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("Current game instance hasn't implemented IMenuInterface yet!"));
		return;
	}
	IMenuInterface::Execute_Host(CurrentGameInstance);
}

void UMainMenuUI::JoinServer()
{
	if(!IsValid(IpAddress)) return;
	APlayerController* OwningPlayerController = GetOwningPlayer();
	if(!OwningPlayerController->Implements<UMenuInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("Current player controller hasn't implemented IMenuInterface yet!"));
		return;
	}
	IMenuInterface::Execute_Join(OwningPlayerController, IpAddress->GetText().ToString());
}

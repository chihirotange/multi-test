// Fill out your copyright notice in the Description page of Project Settings.
#include "Core/MultiTestGameInstance.h"
#include "Blueprint/UserWidget.h"

void UMultiTestGameInstance::Init()
{
	Super::Init();
}

void UMultiTestGameInstance::Join_Implementation(const FString& IP)
{
}

void UMultiTestGameInstance::Host_Implementation()
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



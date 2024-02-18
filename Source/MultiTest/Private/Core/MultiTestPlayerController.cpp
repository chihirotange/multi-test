// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MultiTestPlayerController.h"

void AMultiTestPlayerController::Join(const FString& IP)
{
	ClientTravel(IP, TRAVEL_Absolute);
}
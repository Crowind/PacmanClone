// Fill out your copyright notice in the Description page of Project Settings.


#include "PacPlayerController.h"

#include "PacPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"


APacPlayerController::APacPlayerController(const FObjectInitializer& ObjectInitializer): APlayerController(ObjectInitializer)
{
	PlayerCameraManagerClass = APacPlayerCameraManager::StaticClass();
		
}



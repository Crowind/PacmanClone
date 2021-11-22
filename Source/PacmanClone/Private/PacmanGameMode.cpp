// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"

#include "PacMazePawn.h"
#include "PacPlayerController.h"
#include "Kismet/GameplayStatics.h"

APacmanGameMode::APacmanGameMode()
{
	DefaultPawnClass = APacMazePawn::StaticClass();
	PlayerControllerClass = APacPlayerController::StaticClass();
	

}

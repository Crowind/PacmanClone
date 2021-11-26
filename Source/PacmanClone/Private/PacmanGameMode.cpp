// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"

#include "PacMazePawn.h"
#include "PacPlayerController.h"
#include "PacScoreItem.h"
#include "Kismet/GameplayStatics.h"



APacmanGameMode::APacmanGameMode()
{
	DefaultPawnClass = APacMazePawn::StaticClass();
	PlayerControllerClass = APacPlayerController::StaticClass();
	

}

void APacmanGameMode::AddPoints(int points)
{
	CurrentScore+=points;
}

bool APacmanGameMode::IsChasingActive()
{
	//TODO
	return true;
}

float APacmanGameMode::GetFrightTime()
{
	return 0;
}

void APacmanGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

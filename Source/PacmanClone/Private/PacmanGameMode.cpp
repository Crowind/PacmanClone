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
	const float TimeStamp =GetWorld()->TimeSeconds;
	const int CurrentIndex =LevelDatas[CurrentLevelIndex]->ScatterChaseDurations->TimeStamps.IndexOfByPredicate( [&](float t) { return TimeStamp<t || t<0 ;});
	if(CurrentIndex==INDEX_NONE)
	{
		return false;
	}
	return LevelDatas[CurrentLevelIndex]->ScatterChaseDurations->IsChasingMode[CurrentIndex];
}

float APacmanGameMode::GetFrightTime()
{
	return LevelDatas[CurrentLevelIndex]->FrightTime;
}

float APacmanGameMode::GetGhostFrightenedSpeed()
{
	return LevelDatas[CurrentLevelIndex]->FrightGhostSpeed;
}

float APacmanGameMode::GetGhostSpeed()
{
	
	return LevelDatas[CurrentLevelIndex]->GhostSpeed;
}

float APacmanGameMode::GetGhostTunnelSpeed()
{
	return LevelDatas[CurrentLevelIndex]->GhostSpeedTunnel;
}

void APacmanGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

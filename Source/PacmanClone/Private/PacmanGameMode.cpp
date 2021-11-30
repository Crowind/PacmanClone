// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"

#include "EngineUtils.h"
#include "PacmanGameInstance.h"
#include "PacMazeGhost.h"
#include "PacMazePawn.h"
#include "PacPlayerController.h"


void APacmanGameMode::PowerPillActivated()
{
	for (TActorIterator<APacMazeGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->EnterFrightenedState();
	}
	lastPillTimestamp = GetWorld()->TimeSeconds;

	ghostPoints = 200;
	
}

void APacmanGameMode::GhostCaught()
{
	AddPoints(ghostPoints);
	ghostPoints*=2;
}

float APacmanGameMode::GetPlayerSpeed()
{
	if(GetWorld()->TimeSince(lastPillTimestamp)<GetFrightTime())
	{
		if(GetWorld()->TimeSince(lastEatenDotTimestamp)<0.2)
		{
			return LevelDatas[CurrentLevelIndex]->FrightPacManEatingSpeed;
		}
		return LevelDatas[CurrentLevelIndex]->FrightPacManSpeed;
		
	}
	
	if(GetWorld()->TimeSince(lastEatenDotTimestamp)<0.2)
	{
		return LevelDatas[CurrentLevelIndex]->PacEatingSpeed;
	}

	return LevelDatas[CurrentLevelIndex]->PacSpeed;
		
	
}


void APacmanGameMode::UpdateEatenDot()
{
	lastEatenDotTimestamp= GetWorld()->TimeSeconds;
	for (TActorIterator<APacMazeGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(!ActorItr->bOutOfHouse)
		{
			ActorItr->CurrentDots++;
		}
	}
	
}

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

void APacmanGameMode::ResetLevel()
{
	Super::ResetLevel();
}

int APacmanGameMode::GetCurrentScore()
{
	return CurrentScore;
}

int APacmanGameMode::GetCurrentLives()
{
	return CurrentLives;
}

int APacmanGameMode::GetCurrentLevelIndex()
{
	return CurrentLevelIndex;
}

bool APacmanGameMode::ShouldReset_Implementation(AActor* ActorToReset)
{
	return Super::ShouldReset_Implementation(ActorToReset);
}

void APacmanGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	CurrentLevelIndex = Cast<UPacmanGameInstance>(GetGameInstance())->level;
	CurrentScore = Cast<UPacmanGameInstance>(GetGameInstance())->score;
	CurrentLives = Cast<UPacmanGameInstance>(GetGameInstance())->lives;
	
	Super::InitGame(MapName, Options, ErrorMessage);
}

void APacmanGameMode::InitGameState()
{
	Super::InitGameState();
}

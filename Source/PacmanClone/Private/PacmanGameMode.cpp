// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"

#include "EngineUtils.h"
#include "PacmanGameInstance.h"
#include "PacMazeGhost.h"
#include "PacMazePawn.h"
#include "PacPlayerController.h"
#include "Kismet/GameplayStatics.h"


void APacmanGameMode::PowerPillActivated()
{
	lastPillTimestamp = GetWorld()->TimeSeconds;
	for (TActorIterator<APacMazeGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->EnterFrightenedState();
	}
	ghostPoints = 200;
	
}

float APacmanGameMode::GhostCaught()
{
	AddPoints(ghostPoints);
	float OldGhostPoints = ghostPoints;
	ghostPoints*=2;
	return OldGhostPoints;
}

bool APacmanGameMode::IsPlayerEating() const
{
	return GetWorld()->TimeSince(lastEatenDotTimestamp) < 0.2;
}

float APacmanGameMode::GetPlayerSpeed()
{
	if(GetWorld()->TimeSince(lastPillTimestamp)<GetFrightTime())
	{
		if(IsPlayerEating())
		{
			return LevelDatas[CurrentLevelIndex]->FrightPacManEatingSpeed;
		}
		return LevelDatas[CurrentLevelIndex]->FrightPacManSpeed;
		
	}
	
	if(IsPlayerEating())
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

int APacmanGameMode::BlinkyAngryLevel()
{
	if(APacScoreItem::WinItemCount<LevelDatas[CurrentLevelIndex]->BlinkySpeedThreshold2)
	{
		return 2;
	}
	if(APacScoreItem::WinItemCount<LevelDatas[CurrentLevelIndex]->BlinkySpeedThreshold1)
	{
		return 1;
	}
	
	return 0;
}

float APacmanGameMode::GetBlinkySpeedMultiplier()
{
	switch (BlinkyAngryLevel())
	{
	case 2:
		{
			return LevelDatas[CurrentLevelIndex]->BlinkySpeedUpgrade2;
		}
	case 1:
		{
			return LevelDatas[CurrentLevelIndex]->BlinkySpeedUpgrade1;
		}
	default:
		{
			return LevelDatas[CurrentLevelIndex]->GhostSpeed;
		}
	
	}
	
}

void APacmanGameMode::HandleDeath()
{
	if(SpawnedItem!=nullptr)
	{
		SpawnedItem->Destroy();
	}
	
	if(CurrentLives==0)
	{
		auto gameinstance = Cast<UPacmanGameInstance>(GetGameInstance());
		gameinstance->level=0;
		gameinstance->lives=3;
		gameinstance->score=0;

		GameManager->Death(true);
	}
	else
	{
		GameManager->Death(false);
		CurrentLives--;
	}	
	
	
	
}

APacmanGameMode::APacmanGameMode()
{
	DefaultPawnClass = APacMazePawn::StaticClass();
	PlayerControllerClass = APacPlayerController::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
}

void APacmanGameMode::AddPoints(int points)
{
	CurrentScore+=points;
}

bool APacmanGameMode::IsChasingActive()
{
	const float TimeStamp =GetWorld()->TimeSince(startTime);
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

int APacmanGameMode::GetKlydeDotsDefaultThreshold()
{
	return LevelDatas[CurrentLevelIndex]->KlydeDotsThreshold;
}

int APacmanGameMode::GetInkyDotsDefaultThreshold()
{
	return LevelDatas[CurrentLevelIndex]->InkyDotsThreshold;
}

void APacmanGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(APacScoreItem::WinItemCount== 0)
	{
		Cast<UPacmanGameInstance>(GetGameInstance())->level = FMath::Min(CurrentLevelIndex+1,LevelDatas.Num()-1) ;
		Cast<UPacmanGameInstance>(GetGameInstance())->score = CurrentScore;
		Cast<UPacmanGameInstance>(GetGameInstance())->lives = CurrentLives;

		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

	}
	else if(APacScoreItem::WinItemCount== 274 && SpawnedItem==nullptr)
	{
		SpawnedItem = GetWorld()->SpawnActor(LevelDatas[CurrentLevelIndex]->BonusItem);
		SpawnedItem->SetActorLocation(FVector(0,60,40));
	}
	else if(APacScoreItem::WinItemCount== 174 && SpawnedItem==nullptr)
	{
		SpawnedItem = GetWorld()->SpawnActor(LevelDatas[CurrentLevelIndex]->BonusItem);
		SpawnedItem->SetActorLocation(FVector(0,60,40));
	}
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


void APacmanGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	CurrentLevelIndex = Cast<UPacmanGameInstance>(GetGameInstance())->level;
	CurrentScore = Cast<UPacmanGameInstance>(GetGameInstance())->score;
	CurrentLives = Cast<UPacmanGameInstance>(GetGameInstance())->lives;
	
	Super::InitGame(MapName, Options, ErrorMessage);
}

void APacmanGameMode::ResetTime()
{
	startTime = GetWorld()->TimeSeconds;
}

void APacmanGameMode::BeginPlay()
{
	Super::BeginPlay();
	startTime = AActor::GetWorld()->TimeSeconds;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacScoreItem.h"
#include "GameFramework/GameModeBase.h"
#include "PacmanGameMode.generated.h"


UCLASS()
class UScatterChaseDurations:public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> TimeStamps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> IsChasingMode;
};


UCLASS()
class ULevelData:public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UScatterChaseDurations* ScatterChaseDurations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APacScoreItem* BonusItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PacSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PacEatingSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GhostSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GhostSpeedTunnel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlinkySpeedThreshold1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlinkySpeedUpgrade1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlinkySpeedThreshold2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlinkySpeedUpgrade2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrightTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrightPacManSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrightPacManEatingSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrightGhostSpeed;
	
};

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacmanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APacmanGameMode();
//TODO Current Level Index
	UFUNCTION(BlueprintCallable)
	void AddPoints(int points);
	UFUNCTION(BlueprintCallable)
	bool IsChasingActive();
	UFUNCTION(BlueprintCallable)
	float GetFrightTime();
	UFUNCTION(BlueprintCallable)
	float GetGhostFrightenedSpeed();
	UFUNCTION(BlueprintCallable)
	float GetGhostSpeed();
	UFUNCTION(BlueprintCallable)
	float GetGhostTunnelSpeed();
	
private:
	UPROPERTY(EditAnywhere)
	TArray<ULevelData*> LevelDatas;
	
	UPROPERTY(EditAnywhere)
	int CurrentLevelIndex=0;
private:
	UPROPERTY(VisibleAnywhere)
	int CurrentScore;

public:
	virtual void Tick(float DeltaSeconds) override;
};

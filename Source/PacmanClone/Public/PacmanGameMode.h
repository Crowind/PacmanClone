// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacmanGameInstance.h"
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
	TSubclassOf<APacScoreItem> BonusItem;
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int InkyDotsThreshold;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int KlydeDotsThreshold;
};

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacmanGameMode : public AGameModeBase
{
	GENERATED_BODY()

	float lastPillTimestamp;
	float lastEatenDotTimestamp;
	float ghostPoints;

	int PinkyRespawnDotsThreshold = 7;
	int InkyRespawnDotsThreshold = 17;
	int KlydeRespawnDotsThreshold = 32;

public:

	UFUNCTION(BlueprintCallable)
	void PowerPillActivated();
	UFUNCTION(BlueprintCallable)
	void GhostCaught();
	UFUNCTION(BlueprintCallable)
	float GetPlayerSpeed();
	UFUNCTION(BlueprintCallable)
	void UpdateEatenDot();
	
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

	UPROPERTY(VisibleAnywhere)
	int CurrentScore;
	UPROPERTY(VisibleAnywhere)
	int CurrentLives;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void ResetLevel() override;

	UFUNCTION(BlueprintCallable)
	virtual int GetCurrentScore();
	UFUNCTION(BlueprintCallable)
	virtual int GetCurrentLives();
	UFUNCTION(BlueprintCallable)
	virtual int GetCurrentLevelIndex();
	
	virtual bool ShouldReset_Implementation(AActor* ActorToReset) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
};

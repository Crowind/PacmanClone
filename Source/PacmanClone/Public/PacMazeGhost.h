// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazePawn.h"
#include "PaperFlipbookComponent.h" 
#include "PacMazeGhost.generated.h"

UENUM(BlueprintType)
enum EPacGhostState
{
	Scattering,
	Chasing,
	Frightened,
	FrightenedEnding,
	Eaten
};


/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacMazeGhost : public APacMazePawn
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent * PaperFlipbookComponent;

public:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UAudioComponent* EatenAudioComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bOutOfHouse;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DotsThreshold;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CurrentDots;

	
	explicit APacMazeGhost(const FObjectInitializer& ObjectInitializer);
	
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bCanSteer = true;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	// ReSharper disable once UnrealHeaderToolParserError
	UPaperFlipbook* FlipbookUp;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookLeft;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookRight;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookDown;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookFrightened;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookFrightenedEnding;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookEatenUp;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookEatenLeft;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookEatenRight;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UPaperFlipbook* FlipbookEatenDown;
	
	UFUNCTION(BlueprintCallable)
	UPaperFlipbookComponent* GetPaperFlipbookComponent();
	
	
	UFUNCTION(BlueprintCallable)
	void FlipDirection();

	UFUNCTION(BlueprintCallable)
	void EnterFrightenedState();
	
	UFUNCTION(BlueprintCallable)
	void OnExitFrightenedState();
	UFUNCTION(BlueprintCallable)
	void SetSteering(bool bCond);

	virtual TEnumAsByte<EMazeDirection> GetDisplayedDirection() override;
	
	UFUNCTION(BlueprintCallable)
	void FlipSteering();

	UFUNCTION(BlueprintNativeEvent)
	void InitGhost(bool respawn);

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void GetEaten();
};

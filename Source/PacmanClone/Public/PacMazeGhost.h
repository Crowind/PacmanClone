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
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent * PaperFlipbookComponent;
	
public:
	explicit APacMazeGhost(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookUp;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookLeft;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookRight;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookDown;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookFrightened;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookFrightenedEnding;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookEatenUp;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookEatenLeft;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookEatenRight;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPaperFlipbook* FlipbookEatenDown;

	
	UFUNCTION(BlueprintCallable)
	void FlipDirection();
	UFUNCTION(BlueprintCallable)
	UPaperFlipbookComponent* GetPaperFlipbookComponent();
};

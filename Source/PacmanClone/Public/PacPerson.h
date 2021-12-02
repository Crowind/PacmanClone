// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazePawn.h"
#include "PacPerson.generated.h"

class APacGameManager;
/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacPerson : public APacMazePawn
{
	GENERATED_BODY()

public:
	explicit APacPerson(const FObjectInitializer& ObjectInitializer);
	void PlayDeath();


private:
	virtual void Tick(float DeltaSeconds) override;
public:
	void FlipSteering();

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UAudioComponent* DeathAudioComponent;
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool bCanSteer=true;

	virtual void SetMovementDirection(EMazeDirection Direction) override;

	virtual TEnumAsByte<EMazeDirection> GetDisplayedDirection() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void InitPacPerson();
	UFUNCTION(BlueprintNativeEvent)
	void InitPacPersonAppereance();
	
};

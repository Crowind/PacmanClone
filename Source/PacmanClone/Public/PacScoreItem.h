// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EmptyActor.h"
#include "PacScoreItem.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacScoreItem : public AEmptyActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Score;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	void Consume();
};

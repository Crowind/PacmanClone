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

	static APacScoreItem* firstItem;
	
public:
	static int WinItemCount;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Score;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bWinRequisite;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintNativeEvent)
	void Consume();

	static int GetWinItemsCount();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};


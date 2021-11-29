// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacLink.h"
#include "PacNode.h"
#include "GatePacLink.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API AGatePacLink : public APacLink
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int DotsCount;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int DotsThreshold;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EMazeDirection> Head1Direction;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EMazeDirection> Head2Direction;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bOneWay;

	UFUNCTION(BlueprintCallable)
	virtual void Close();
	
	UFUNCTION(BlueprintCallable)
	virtual void Open();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};

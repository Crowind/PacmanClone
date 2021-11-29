// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacNode.h"
#include "PriorityPacNode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APriorityPacNode : public APacNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EMazeDirection> PriorityDirection;

	virtual void Tick(float DeltaSeconds) override;
	
};

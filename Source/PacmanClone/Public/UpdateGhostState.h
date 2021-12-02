// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacmanGameMode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UpdateGhostState.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API UUpdateGhostState : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector PacGhostStateKeySelector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector FrightenedTimeStampKeySelector;

	void UpdateDefaultBehaviour(UBehaviorTreeComponent& OwnerComp, APacmanGameMode* GameMode, EPacGhostState State,
	                            APacMazeGhost* Ghost);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetPacGhostState.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API USetPacGhostState : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector PacGhostStateKeySelector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector NewGhostStateKeySelector;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

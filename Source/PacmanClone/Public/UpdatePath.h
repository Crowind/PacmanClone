// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UpdatePath.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API UUpdatePath : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector DestinationKeySelector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector PawnKeySelector;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

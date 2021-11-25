// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AssignChasingDestinationKlyde.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API UAssignChasingDestinationKlyde : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector ChasingDestinationKeySelector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector ScatteringDestinationKeySelector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector TargetActorKeySelector;
	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

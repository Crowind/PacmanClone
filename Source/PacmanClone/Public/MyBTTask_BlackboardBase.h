// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API USetCurrentDirection : public UBTTaskNode
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bUseActorAsTarget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector CurrentDestinationKeySelector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector TargetDestinationKeySelector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(EditCondition="BUseActorAsTarget"))
	FBlackboardKeySelector TargetActorKeySelector;

	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

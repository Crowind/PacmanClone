// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBTTask_BlackboardBase.h"
#include "SetCurrentRandomDirection.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API USetCurrentRandomDirection : public UBTTaskNode
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector CurrentDestinationKeySelector;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

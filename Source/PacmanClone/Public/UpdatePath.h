// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacNode.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UpdatePath.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API UUpdatePath : public UBTService
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector DestinationKeySelector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanFlip;
	

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};

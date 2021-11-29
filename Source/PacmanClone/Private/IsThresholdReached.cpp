// Fill out your copyright notice in the Description page of Project Settings.


#include "IsThresholdReached.h"

#include "AIController.h"
#include "PacMazeGhost.h"

EBTNodeResult::Type UIsThresholdReached::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());


	return Ghost->CurrentDots>=Ghost->DotsThreshold? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

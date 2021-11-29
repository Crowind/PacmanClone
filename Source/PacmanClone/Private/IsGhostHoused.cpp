// Fill out your copyright notice in the Description page of Project Settings.


#include "IsGhostHoused.h"

#include "AIController.h"
#include "PacMazeGhost.h"

EBTNodeResult::Type UIsGhostHoused::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	return Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn())->bOutOfHouse? EBTNodeResult::Failed: EBTNodeResult::Succeeded;
}

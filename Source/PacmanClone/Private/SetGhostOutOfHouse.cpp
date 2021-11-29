// Fill out your copyright notice in the Description page of Project Settings.


#include "SetGhostOutOfHouse.h"

#include "AIController.h"
#include "PacMazeGhost.h"

EBTNodeResult::Type USetGhostOutOfHouse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());
	Ghost->bOutOfHouse=NewValue;
	
	return EBTNodeResult::Succeeded;
}

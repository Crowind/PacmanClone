// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateHousePath.h"

#include "AIController.h"
#include "PacMazeGhost.h"
#include "PacUtilities.h"

EBTNodeResult::Type UUpdateHousePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	Ghost->SetDisplayDirection(Opposite(Ghost->GetMovementDirection()));
	
	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateHousePath.h"

#include "AIController.h"
#include "PacMazeGhost.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUpdateHousePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	const bool bHouseBool = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsBool(HouseBoolKey.SelectedKeyName);
	if(!bHouseBool)
	{
		Ghost->SetDisplayDirection(Opposite(Ghost->GetMovementDirection()));
	}

	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "SetPacGhostState.h"

#include "AIController.h"
#include "IsGhostStateEqualTo.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USetPacGhostState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const EPacGhostState NewState = static_cast<EPacGhostState>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum(NewGhostStateKeySelector.SelectedKeyName));
	
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName,NewState);
	
	return EBTNodeResult::Succeeded;
}

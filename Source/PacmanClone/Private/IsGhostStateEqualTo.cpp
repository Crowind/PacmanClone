// Fill out your copyright notice in the Description page of Project Settings.


#include "IsGhostStateEqualTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"

EBTNodeResult::Type UIsGhostStateEqualTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const EPacGhostState State = static_cast<EPacGhostState>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName));
	
	return State==ComparisonState.GetValue()?EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

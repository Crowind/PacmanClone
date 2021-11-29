// Fill out your copyright notice in the Description page of Project Settings.


#include "IsEatenDestinationReached.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UIsEatenDestinationReached::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const FVector CurrentPosition = OwnerComp.GetAIOwner()->GetPawn()->GetTransform().GetLocation();

	const FVector Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(EatenDestinationSelectorKey.SelectedKeyName);
	
	return  FVector::DistXY(CurrentPosition,Destination) <10 ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "IsTargetActorReached.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UIsTargetActorReached::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AActor* TargetActor = Cast<AActor> (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorSelectorKey.SelectedKeyName));

	TArray<AActor*> OverlappingActors;
	
	OwnerComp.GetAIOwner()->GetPawn()->GetOverlappingActors(OverlappingActors);

	return  OverlappingActors.Contains(TargetActor) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

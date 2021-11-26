// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignChasingDestinationKlyde.h"

#include "AIController.h"
#include "PacMazePawn.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAssignChasingDestinationKlyde::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APacMazePawn* Player = Cast<APacMazePawn>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorKeySelector.SelectedKeyName));

	FVector Destination = Player->GetTransform().GetLocation();

	if((Destination - OwnerComp.GetAIOwner()->GetPawn()->GetTransform().GetLocation()).Size()<240)
	{
		Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(ScatteringDestinationKeySelector.SelectedKeyName);
	}
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(ChasingDestinationKeySelector.SelectedKeyName,Destination);
	
	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_BlackboardBase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USetCurrentDirection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector Destination;

	if(bUseActorAsTarget)
	{
		Destination = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorKeySelector.SelectedKeyName))->GetTransform().GetLocation();
	}
	else
	{
		Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(TargetDestinationKeySelector.SelectedKeyName);
	}

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(CurrentDestinationKeySelector.SelectedKeyName,Destination);
	
	
	return EBTNodeResult::Succeeded;
}

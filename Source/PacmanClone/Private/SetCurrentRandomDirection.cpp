// Fill out your copyright notice in the Description page of Project Settings.


#include "SetCurrentRandomDirection.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type USetCurrentRandomDirection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector Destination = OwnerComp.GetAIOwner()->GetPawn()->GetTransform().GetLocation();

	Destination = UKismetMathLibrary::RandomPointInBoundingBox(Destination,FVector(1000,1000,0));
	
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(CurrentDestinationKeySelector.SelectedKeyName,Destination);
	return EBTNodeResult::Succeeded;
}

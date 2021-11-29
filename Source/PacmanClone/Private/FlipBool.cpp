// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipBool.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFlipBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	const bool bHouseBool = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsBool(HouseBoolKey.SelectedKeyName);
	if(!bHouseBool)
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(HouseBoolKey.SelectedKeyName,true);
	}
	else
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(HouseBoolKey.SelectedKeyName,false);
	}
	
	return EBTNodeResult::Succeeded;
}

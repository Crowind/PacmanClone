// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignChasingDestinationPinky.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAssignChasingDestinationPinky::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APacMazePawn* Player = Cast<APacMazePawn>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorKeySelector.SelectedKeyName));
	FVector Destination = Player->GetTransform().GetLocation();

	switch (Player->GetMovementDirection())
	{
	case Up:
		{
			Destination+= (MazeDirectionToVector(Up)+MazeDirectionToVector(Left)) *120;
			break;
		}
	case Left:
		{
			Destination+= MazeDirectionToVector(Left) *120;
			break;
		}
	case Right:
		{
			Destination+= MazeDirectionToVector(Right) *120;
			break;
		}
	case Down:
		{
			Destination+= MazeDirectionToVector(Down) *120;
			break;
		}
	default: break;
	}

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(ChasingDestinationKeySelector.SelectedKeyName,Destination);

	DrawDebugLine( OwnerComp.GetAIOwner()->GetPawn()->GetWorld(),OwnerComp.GetAIOwner()->GetPawn()->GetTransform().GetLocation(),Destination,FColor::Magenta);	
	
	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignChasingDestinationInky.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "PacMazeGhost.h"
#include "PacMazePawn.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAssignChasingDestinationInky::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APacMazePawn* Player = Cast<APacMazePawn>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorKeySelector.SelectedKeyName));
	APacMazeGhost* Blinky = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(BlinkyKeySelector.SelectedKeyName));
	FVector Destination = Player->GetTransform().GetLocation();

	switch (Player->GetMovementDirection())
	{
	case Up:
		{
			Destination+= (MazeDirectionToVector(Up)+MazeDirectionToVector(Left)) *60;
			break;
		}
	case Left:
		{
			Destination+= MazeDirectionToVector(Left) *60;
			break;
		}
	case Right:
		{
			Destination+= MazeDirectionToVector(Right) *60;
			break;
		}
	case Down:
		{
			Destination+= MazeDirectionToVector(Down) *60;
			break;
		}
	default: break;
	}

	Destination += Destination - Blinky->GetTransform().GetLocation();

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(ChasingDestinationKeySelector.SelectedKeyName,Destination);
	
	return EBTNodeResult::Succeeded;
}

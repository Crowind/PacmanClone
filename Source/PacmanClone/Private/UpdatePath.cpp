// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdatePath.h"

#include "AIController.h"
#include "PacLink.h"
#include "PacMazeGhost.h"
#include "PacMazePawn.h"
#include "PacNode.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"


void UUpdatePath::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	const FVector Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(DestinationKeySelector.SelectedKeyName);
	

	if(Ghost==nullptr)
	{
		return;
	}

	APacLink* CurrentPacLink = Cast<APacLink>(Ghost->CurrentZone);

	if(CurrentPacLink && CurrentPacLink->mapping.Contains(Ghost->GetMovementDirection()))
	{
		APacNode* ApproachingNode = static_cast<APacNode*> (CurrentPacLink->mapping[Ghost->GetMovementDirection()]);

		TSortedMap< float, TEnumAsByte<EMazeDirection>> CostsToDirectionsMap;
		
		if( (bCanFlip ||Opposite(Ghost->GetMovementDirection())!= Up) && ApproachingNode->UpLink!=nullptr)
		{
			const float Cost = FVector::DistXY(ApproachingNode->GetTransform().GetLocation() + 30 * MazeDirectionToVector(Up), Destination);
			CostsToDirectionsMap.Add(Cost,Up);
		}
		if( (bCanFlip ||Opposite(Ghost->GetMovementDirection())!= Left) && ApproachingNode->LeftLink!=nullptr)
		{
			const float Cost = FVector::DistXY(ApproachingNode->GetTransform().GetLocation() + 30 * MazeDirectionToVector(Left), Destination);
			CostsToDirectionsMap.Add(Cost,Left);
		}
		if( (bCanFlip ||Opposite(Ghost->GetMovementDirection())!= Right) && ApproachingNode->RightLink!=nullptr)
		{
			const float Cost = FVector::DistXY(ApproachingNode->GetTransform().GetLocation() + 30 * MazeDirectionToVector(Right), Destination);
			CostsToDirectionsMap.Add(Cost,Right);
		}
		if( (bCanFlip ||Opposite(Ghost->GetMovementDirection())!= Down) && ApproachingNode->BottomLink!=nullptr)
		{
			const float Cost = FVector::DistXY(ApproachingNode->GetTransform().GetLocation() + 30 * MazeDirectionToVector(Down), Destination);
			CostsToDirectionsMap.Add(Cost,Down);
		}

		TArray<TEnumAsByte<EMazeDirection>>ValuesArray;
		CostsToDirectionsMap.GenerateValueArray( ValuesArray);
		
		if(ValuesArray.Num()>0)
		{
			Ghost->SetDisplayDirection(ValuesArray[0]);
		}
		else
		{
			Ghost->FlipDirection();
		}
		
	}
	return;
}

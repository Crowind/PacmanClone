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



EBTNodeResult::Type UUpdatePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	const FVector Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(DestinationKeySelector.SelectedKeyName);
	

	if(Ghost==nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APacLink* CurrentPacLink = Cast<APacLink>(Ghost->CurrentZone);

	if(CurrentPacLink)
	{
		APacNode* ApproachingNode = static_cast<APacNode*> (CurrentPacLink->mapping[Ghost->GetMovementDirection()]);

		TSortedMap< float, TEnumAsByte<EMazeDirection>> CostsToDirectionsMap;
		
		if(Opposite(Ghost->GetMovementDirection())!= Up && ApproachingNode->UpLink!=nullptr)
		{
			const float Cost = ApproachingNode->UpLink->Cost + FVector::DistXY(ApproachingNode->UpLink->mapping[Up]->GetTransform().GetLocation(), Destination);
			CostsToDirectionsMap.Add(Cost,Up);
		}
		if(Opposite(Ghost->GetMovementDirection())!= Left && ApproachingNode->LeftLink!=nullptr)
		{
			const float Cost = ApproachingNode->LeftLink->Cost + FVector::DistXY(ApproachingNode->LeftLink->mapping[Left]->GetTransform().GetLocation(), Destination);
			CostsToDirectionsMap.Add(Cost,Left);
		}
		if(Opposite(Ghost->GetMovementDirection())!= Right && ApproachingNode->RightLink!=nullptr)
		{
			const float Cost = ApproachingNode->RightLink->Cost + FVector::DistXY(ApproachingNode->RightLink->mapping[Right]->GetTransform().GetLocation(), Destination);
			CostsToDirectionsMap.Add(Cost,Right);
		}
		if(Opposite(Ghost->GetMovementDirection())!= Down && ApproachingNode->BottomLink!=nullptr)
		{
			const float Cost = ApproachingNode->BottomLink->Cost + FVector::DistXY(ApproachingNode->BottomLink->mapping[Down]->GetTransform().GetLocation(), Destination);
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
			FString s = UEnum::GetValueAsString(Ghost->GetMovementDirection().GetValue());
			Ghost->FlipDirection();
			s.Append(" ").Append(UEnum::GetValueAsString(Ghost->GetMovementDirection().GetValue()));
			GEngine->AddOnScreenDebugMessage(-1,1,FColor::Yellow,s);
		}
		
	}
	return EBTNodeResult::Succeeded;
}

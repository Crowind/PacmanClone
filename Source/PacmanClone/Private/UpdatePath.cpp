// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdatePath.h"

#include "AIController.h"
#include "PacLink.h"
#include "PacMazePawn.h"
#include "PacNode.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"



EBTNodeResult::Type UUpdatePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazePawn* Ghost = Cast<APacMazePawn>(OwnerComp.GetAIOwner()->GetPawn());

	const FVector Destination = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(DestinationKeySelector.SelectedKeyName);
	

	if(Ghost==nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APacMazeZone* CurrentPacMazeZone = Ghost->CurrentZone;

	APacLink* CurrentPacLink = Cast<APacLink>(CurrentPacMazeZone);

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

		// TArray<float>KeysArray;
		// CostsToDirectionsMap.GenerateKeyArray( KeysArray);
		//
		// FString s;
		// for (auto Value : ValuesArray)
		// {
		// 	s.Append(UEnum::GetValueAsString(Value));
		// 	s.Append(TEXT("   -   "));
		// }
		// FString s2;
		// for (auto Key : KeysArray)
		// {
		// 	s2.Append(FString::SanitizeFloat(Key));
		// 	s2.Append(TEXT("   -   "));
		// }
 	//
		// GEngine->AddOnScreenDebugMessage(-1,0.2,FColor::Emerald,s);
		// GEngine->AddOnScreenDebugMessage(-1,0.2,FColor::Orange,s2);
		//
		Ghost->SetDisplayDirection(ValuesArray[0]);
		
	}
	return EBTNodeResult::Succeeded;
}

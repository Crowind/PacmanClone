// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateGhostState.h"

#include "AIController.h"
#include "PacmanGameMode.h"
#include "PacMazeGhost.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUpdateGhostState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APacmanGameMode* GameMode = Cast<APacmanGameMode> (GetWorld()->GetAuthGameMode());
	
	auto State = static_cast<EPacGhostState>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName));

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	switch(State)
	{
	case Frightened:
		{
			float LastFrightening = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsFloat(FrightenedTimeStampKeySelector.SelectedKeyName);
			if(GetWorld()->TimeSince(LastFrightening)>=GameMode->GetFrightTime()-3)
			{
				OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName,FrightenedEnding);
				break;
			}
			
		}
	case FrightenedEnding:
		{
			float LastFrightening = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsFloat(FrightenedTimeStampKeySelector.SelectedKeyName);
			if(GetWorld()->TimeSince(LastFrightening)>=GameMode->GetFrightTime())
			{
				Ghost->OnExitFrightenedState();
			}
			else
			{
				break;
			}
			
		}
	case Eaten:	
	case Scattering:
	case Chasing:
		{
			EPacGhostState NewState = GameMode->IsChasingActive()?Chasing:Scattering;

			if(NewState!=State)
			{
				Ghost->FlipDirection();
				//GEngine->AddOnScreenDebugMessage(-1,6,FColor::Orange,FString().Append(Ghost->GetName()).Append(" ").Append(UEnum::GetValueAsString(NewState)));
			}
			
			OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName,NewState);
			break;
		}
	default: break;
	}
	return EBTNodeResult::Succeeded;
	
}

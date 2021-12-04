// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateGhostState.h"

#include "AIController.h"
#include "PacmanGameMode.h"
#include "PacMazeGhost.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AudioComponent.h"

void UUpdateGhostState::UpdateDefaultBehaviour(UBehaviorTreeComponent& OwnerComp, APacmanGameMode* GameMode, EPacGhostState State, APacMazeGhost* Ghost)
{
	EPacGhostState NewState = GameMode->IsChasingActive()?Chasing:Scattering;

	if(NewState!=State && Ghost->bOutOfHouse)
	{
		Ghost->FlipDirection();
	}
			
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName,NewState);
}

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
				UpdateDefaultBehaviour(OwnerComp, GameMode, State, Ghost);
				break;
			}
			break;
		}
	case Eaten:
		{
			Ghost->EatenAudioComponent->Stop();
			Ghost->bOutOfHouse=false;
		}
	case Scattering:
	case Chasing:
		{
			UpdateDefaultBehaviour(OwnerComp, GameMode, State, Ghost);
			break;
		}
	default: break;
	}
	
	return EBTNodeResult::Succeeded;
	
}

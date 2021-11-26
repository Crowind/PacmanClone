// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateGhostSpeed.h"

#include "AIController.h"
#include "PacLink.h"
#include "PacmanGameMode.h"
#include "PacMazeGhost.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUpdateGhostSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());
	
	APacmanGameMode* GameMode = Cast<APacmanGameMode> (GetWorld()->GetAuthGameMode());

	if(Ghost->CurrentZone->Tags.Contains(FName("Tunnel")))
	{
		Ghost->SetSpeedModifier(GameMode->GetGhostTunnelSpeed());

		return EBTNodeResult::Succeeded;
	}
	
	auto State = static_cast<EPacGhostState>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName));

	switch (State) {
		case Frightened:
		case FrightenedEnding:
			{
				Ghost->SetSpeedModifier(GameMode->GetGhostFrightenedSpeed());
				break;
			}
		case Scattering:
		case Chasing:
			{
				Ghost->SetSpeedModifier(GameMode->GetGhostSpeed());
				break;
			}
		case Eaten:
			{
				Ghost->SetSpeedModifier(1);
				break;
			}	
		default: ;
	}
	
	return EBTNodeResult::Succeeded;
}

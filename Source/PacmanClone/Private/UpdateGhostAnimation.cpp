// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateGhostAnimation.h"

#include "AIController.h"
#include "IsGhostStateEqualTo.h"
#include "PacMazeGhost.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUpdateGhostAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APacMazeGhost* Ghost = Cast<APacMazeGhost>(OwnerComp.GetAIOwner()->GetPawn());

	const EPacGhostState CurrentState = static_cast<EPacGhostState>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum(PacGhostStateKeySelector.SelectedKeyName));

	switch (CurrentState)
	{
		case Scattering:
		case Chasing:
			{
				switch (Ghost->GetMovementDirection())
				{
					case Up:
						{
							Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookUp);
							break;
						}
					case Left:
						{
							Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookLeft);
							break;
						}
					case Right:
						{
							Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookRight);
							break;
						}
					case Down:
						{
							Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookDown);
							break;
						}
					default: ;
					}
				break;
			}
		case Frightened:
			{
				Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookFrightened);
				break;
			}
		case FrightenedEnding:
			{
				Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookFrightenedEnding);
				break;
			}
		case Eaten:
			{
				switch (Ghost->GetMovementDirection())
				{
				case Up:
					{
						Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookEatenUp);
						break;
					}
				case Left:
					{
						Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookEatenLeft);
						break;
					}
				case Right:
					{
						Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookEatenRight);
						break;
					}
				case Down:
					{
						Ghost->GetPaperFlipbookComponent()->SetFlipbook(Ghost->FlipbookEatenDown);
						break;
					}
				default: ;
				}
				break;
			}
		default: ;
	}
	return EBTNodeResult::Succeeded;
}

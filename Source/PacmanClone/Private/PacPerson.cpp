// Fill out your copyright notice in the Description page of Project Settings.


#include "PacPerson.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PacGameManager.h"
#include "PacmanGameMode.h"
#include "PacMazeGhost.h"
#include "PacScoreItem.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AudioComponent.h"

APacPerson::APacPerson(const FObjectInitializer& ObjectInitializer): APacMazePawn(ObjectInitializer)
{
	
	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Death Audio Component"));
	DeathAudioComponent->SetupAttachment(RootComponent);
	
}

void APacPerson::PlayDeath_Implementation()
{
	DeathAudioComponent->SetPaused(false);
	DeathAudioComponent->Play();
}


void APacPerson::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TArray<AActor*> ScoreItems;
	TArray<AActor*> Ghosts;
	
	GetOverlappingActors(ScoreItems,APacScoreItem::StaticClass());

	for (AActor* ScoreItem : ScoreItems)
	{
		Cast<APacScoreItem>(ScoreItem)->Consume();
	}

	GetOverlappingActors(Ghosts,APacMazeGhost::StaticClass());

	for (AActor* Ghost : Ghosts)
	{
		auto ghost = Cast<APacMazeGhost>(Ghost);

		AAIController* aiController = Cast<AAIController>(ghost->GetController());
		if(aiController==nullptr || aiController->BrainComponent == nullptr || !aiController->BrainComponent->IsRunning() )
		{
			continue;
		}
		const EPacGhostState state = static_cast<EPacGhostState>(aiController->GetBlackboardComponent()->GetValueAsEnum(FName("GhostCurrentState")));

		if(state == Chasing || state == Scattering)
		{
			Cast<APacmanGameMode>(GetWorld()->GetAuthGameMode())->HandleDeath();
		}
		else if(state == Frightened || state == FrightenedEnding)
		{
			ghost->GetEaten();
		}
		
	}

	SetSpeedModifier( Cast<APacmanGameMode>(GetWorld()->GetAuthGameMode())->GetPlayerSpeed() );
	
}

void APacPerson::FlipSteering()
{
	bCanSteer = !bCanSteer;
}

void APacPerson::SetMovementDirection(EMazeDirection Direction)
{
		Super::SetMovementDirection(Direction);

}

TEnumAsByte<EMazeDirection> APacPerson::GetDisplayedDirection()
{
	if(!bCanSteer)
	{
		return GetMovementDirection();
	}
	return Super::GetDisplayedDirection();
}

void APacPerson::BeginPlay()
{
	SetMovementDirection(Left);
	SetDisplayDirection(Left);
	DeathAudioComponent->SetPaused(true);
	Super::BeginPlay();
}

void APacPerson::InitPacPersonAppereance_Implementation()
{
}


void APacPerson::InitPacPerson_Implementation()
{
}

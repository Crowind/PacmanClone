// Fill out your copyright notice in the Description page of Project Settings.


#include "PacPerson.h"

#include "PacmanGameMode.h"
#include "PacScoreItem.h"
#include "PacUtilities.h"

void APacPerson::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TArray<AActor*> ScoreItems;
	
	GetOverlappingActors(ScoreItems,APacScoreItem::StaticClass());

	for (AActor* ScoreItem : ScoreItems)
	{
		Cast<APacScoreItem>(ScoreItem)->Consume();
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
	Super::BeginPlay();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeZone.h"

#include "PacMazeGhost.h"

// Sets default values for this component's properties
APacMazeZone::APacMazeZone()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

}


void APacMazeZone::DrawGizmos()
{
}

void APacMazeZone::Assign(APacMazePawn* PacMazePawn)
{
	auto ghost = Cast<APacMazeGhost>(PacMazePawn);
	if(ghost!=nullptr)
	{
		if(bFlipGhostSteering)
		{
			ghost->FlipSteering();
		}
		else
		{
			ghost->SetSteering (!bBlockGhostSteering);	
		}
	}
	
	PacMazePawn->CurrentZone = this;
	CurrentlyHandledPacPawns.Add(PacMazePawn);
	PacMazePawn->SetActorLocation(GetTransform().GetLocation());
	
}

// Called when the game starts
void APacMazeZone::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void APacMazeZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}




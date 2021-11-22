// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeZone.h"

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
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Emerald,this->GetName());
	CurrentlyHandledPacPawns.Add(PacMazePawn);
	PacMazePawn->TeleportTo(GetTransform().GetLocation(),FRotator::ZeroRotator);
	
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


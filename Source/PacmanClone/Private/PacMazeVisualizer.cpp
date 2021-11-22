// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeVisualizer.h"

#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "PacMazeZone.h"

// Sets default values
APacMazeVisualizer::APacMazeVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacMazeVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacMazeVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APacMazeVisualizer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FlushPersistentDebugLines(GetWorld());
	for (TActorIterator<APacMazeZone> ZoneItr(GetWorld()); ZoneItr; ++ZoneItr )
	{
		ZoneItr->DrawGizmos();
		
	}

	
}


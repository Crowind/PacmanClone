// Fill out your copyright notice in the Description page of Project Settings.


#include "PacLink.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "PacMazeGhost.h"
#include "PacMazePawn.h"
#include "PacNode.h"
#include "PacPerson.h"
#include "PacUtilities.h"

// Sets default values
APacLink::APacLink()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

}


void APacLink::InitMapping()
{
	mapping.Empty();
	if(Head1)
	{
		const auto Node1 = Cast<APacNode>(Head1);
		if(Node1)
		{
			if(Node1->BottomLink == this)
			{
				mapping.Add(Up,Head1);
			}
			else if(Node1->LeftLink == this)
			{
				mapping.Add(Right,Head1);
			}
			else if(Node1->UpLink == this)
			{
				mapping.Add(Down,Head1);
			}
			else if(Node1->RightLink == this)
			{
				mapping.Add(Left,Head1);
			}
		}
	}
	if(Head2)
	{
		const auto Node2 = Cast<APacNode>(Head2);
		if(Node2)
		{
			if(Node2->BottomLink == this)
			{
				mapping.Add(Up,Head2);
			}
			else if(Node2->LeftLink == this)
			{
				mapping.Add(Right,Head2);
			}
			else if(Node2->UpLink == this)
			{
				mapping.Add(Down,Head2);
			}
			else if(Node2->RightLink == this)
			{
				mapping.Add(Left,Head2);
			}
		}
	}
}

// Called when the game starts or when spawned
void APacLink::BeginPlay()
{
	Super::BeginPlay();

	Cost = FVector::DistXY(Head1->GetTransform().GetLocation(),Head2->GetTransform().GetLocation());
	
	if(bSpawnPellets)
	{
		for(float i = 1;i<=PelletsAmount;i++)
		{
			AActor* Pellet = (bSpawnSpecialPellet && i-1 == PelletsAmount-i)
				                 ? GetWorld()->SpawnActor(SpecialPellet)
				                 : GetWorld()->SpawnActor(ScoreSpawnType);
			
			FVector PelletLocation =FMath::Lerp( Head1->GetTransform().GetLocation(), Head2->GetTransform().GetLocation(),(i)/(PelletsAmount+1));
			Pellet->SetActorLocation(PelletLocation);
		}
		
	}
	
}

void APacLink::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckPawnsMovement();
}

void APacLink::DrawGizmos()
{
	Super::DrawGizmos();
	
	DrawDebugPoint(GetWorld(),GetTransform().GetLocation() ,24, !(Head1&&Head2) ? FColor::Red: bSpawnPellets?FColor::Yellow : FColor::White,true);
}


void APacLink::TryAttach(APacMazeZone* NewHead)
{
	if(Head1==nullptr)
	{
		Head1 = NewHead;
	}
	else if(Head2 == nullptr)
	{
		Head2 = NewHead;
	}
	
}

float APacLink::InverseLerp(float xx, float yy, float value)
{
	return (value - xx)/(yy - xx);
}


float APacLink::InverseLerp(FVector v1, FVector v2, FVector value)
{
	FVector AB = v2- v1;
	FVector AV = value - v1;
	return FVector::DotProduct(AV, AB) / FVector::DotProduct(AB, AB);
}


void APacLink::Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> entranceDirection)
{
	APacMazeGhost* ghost = Cast<APacMazeGhost>(PacMazePawn);
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
	APacPerson* pacPerson = Cast<APacPerson>(PacMazePawn);
	if(pacPerson!=nullptr)
	{
		if(bFlipPacPersonSteer)
		{
			pacPerson->FlipSteering();
		}
		else
		{
			pacPerson->bCanSteer=true;
		}
	}
	CurrentlyHandledPacPawns.Add(PacMazePawn);
	PacMazePawn->CurrentZone = this;
	PacMazePawn->SetPacMovementActive(true);
	CheckPawnMovement(PacMazePawn);

	if( mapping.Contains(Opposite(entranceDirection)))
	{
		const FVector Entrance = mapping[Opposite(entranceDirection)]->GetTransform().GetLocation(); 
		
		PacMazePawn->SetActorLocation(Entrance);
		
	}
};

void APacLink::CheckPawnMovement(APacMazePawn* PacMazePawn)
{
	auto DisplayedDir = PacMazePawn->GetDisplayedDirection();

	if(mapping.Contains(DisplayedDir))
	{
		PacMazePawn->SetMovementDirection(DisplayedDir);
	}

	TEnumAsByte<EMazeDirection> MovementDirection = PacMazePawn->GetMovementDirection();
	const TEnumAsByte<EMazeDirection> OppositeDirection = Opposite(MovementDirection);

	const FVector PawnLocation = PacMazePawn->GetTransform().GetLocation();

	const float TValue = InverseLerp(mapping[OppositeDirection]->GetTransform().GetLocation(),
	                                 mapping[MovementDirection]->GetTransform().GetLocation(), PawnLocation);
		
	if(TValue >= 1)
	{
		CurrentlyHandledPacPawns.Remove(PacMazePawn);
		mapping[MovementDirection]->Assign(PacMazePawn);
		
	}
}

void APacLink::CheckPawnsMovement()
{
	TArray<APacMazePawn*> CurrentlyHandledPawnsCopy(CurrentlyHandledPacPawns);
	
	for(int i = CurrentlyHandledPacPawns.Num()-1; i>=0;i--)
	{
		APacMazePawn* PacMazePawn = CurrentlyHandledPawnsCopy[i];
		CheckPawnMovement(PacMazePawn);
		
	}
	
}



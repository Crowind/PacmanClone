// Fill out your copyright notice in the Description page of Project Settings.


#include "PacLink.h"

#include "DrawDebugHelpers.h"
#include "PacMazePawn.h"
#include "PacNode.h"

// Sets default values
APacLink::APacLink()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void APacLink::BeginPlay()
{
	Super::BeginPlay();

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

void APacLink::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MovePawns();
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


TEnumAsByte<EMazeDirection> Opposite(const TEnumAsByte<EMazeDirection>& Direction)
{
	switch (Direction) {
	case Down: return Up;
	case Right: return Left;
	case Up: return Down;
	case Left: return Right;
	default: return Direction ;
	}
}

void APacLink::Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> entranceDirection)
{
	CurrentlyHandledPacPawns.Add(PacMazePawn);

	TArray<TEnumAsByte<EMazeDirection>> keys;
	mapping.GetKeys(keys);

	const FVector Entrance = mapping[Opposite(entranceDirection)]->GetTransform().GetLocation(); 
	//
	PacMazePawn->TeleportTo(Entrance,FRotator::ZeroRotator);
};

void APacLink::MovePawns()
{
	for (APacMazePawn* PacMazePawn : CurrentlyHandledPacPawns)
	{
		auto DisplaydDir = PacMazePawn->GetDisplayedDirection();

		if(mapping.Contains(DisplaydDir))
		{
			PacMazePawn->SetMovementDirection(DisplaydDir);
		}

		TEnumAsByte<EMazeDirection> MovementDirection = PacMazePawn->GetMovementDirection();
		const TEnumAsByte<EMazeDirection> OppositeDirection = Opposite(MovementDirection);

		const FVector PawnLocation = PacMazePawn->GetTransform().GetLocation();

		const float TValue = InverseLerp(mapping[OppositeDirection]->GetTransform().GetLocation(),
		                                 mapping[MovementDirection]->GetTransform().GetLocation(), PawnLocation);


		GEngine->AddOnScreenDebugMessage(-1,4,FColor::Red, FString::SanitizeFloat(TValue));
		
		if(TValue >= 1)
		{
			CurrentlyHandledPacPawns.Remove(PacMazePawn);
			mapping[MovementDirection]->Assign(PacMazePawn);
		
		}
		
	}
	
}



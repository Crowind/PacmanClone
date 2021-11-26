// Fill out your copyright notice in the Description page of Project Settings.


#include "PacNode.h"

#include "DrawDebugHelpers.h"
#include "PacMazeGhost.h"
#include "PacUtilities.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
APacNode::APacNode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void APacNode::BeginPlay()
{
	Super::BeginPlay();
	
	if(bSpawnPellets)
	{
		AActor* Pellet = GetWorld()->SpawnActor(ScoreSpawnType);	
		Pellet->SetActorLocation(GetTransform().GetLocation());
	}
	
	
}

bool APacNode::TryAssignPawnToDirection(APacMazePawn* PacMazePawn,TEnumAsByte<EMazeDirection> Direction)
{
	switch (Direction.GetValue())
	{
	case Down:
		{
			if(BottomLink!=nullptr)
			{
				CurrentlyHandledPacPawns.Remove(PacMazePawn);
				BottomLink->Assign(PacMazePawn,Down);
				return true;
			}
			break;
		}
	case Up:
		{
			if(UpLink!=nullptr)
			{
				CurrentlyHandledPacPawns.Remove(PacMazePawn);
				UpLink->Assign(PacMazePawn,Up);

				return true;
			}
			break;
		}
	case Left:
		{
			if(LeftLink!=nullptr)
			{
				CurrentlyHandledPacPawns.Remove(PacMazePawn);
				LeftLink->Assign(PacMazePawn,Left);
				return true;
			}
			break;
		}
	case Right:
		{
			if(RightLink!=nullptr)
			{
				CurrentlyHandledPacPawns.Remove(PacMazePawn);
				RightLink->Assign(PacMazePawn,Right);
				return true;
			}
			break;
		}
	default:
		{
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Orange,TEXT("wtf"));
			return false;
			break;
		}
	}
	return false;
}

void APacNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const int HandledPawns = CurrentlyHandledPacPawns.Num();
	
	for(int i = HandledPawns-1; i>=0;i--)
	{
		APacMazePawn* PacMazePawn = CurrentlyHandledPacPawns[i];
		if(PacMazePawn== nullptr)
		{
			return;
		}
		PacMazePawn->SetPacMovementActive(false);
		
		bool bAssigned = TryAssignPawnToDirection(PacMazePawn,PacMazePawn->GetDisplayedDirection());
		if(!bAssigned)
		{
			TryAssignPawnToDirection(PacMazePawn,PacMazePawn->GetMovementDirection());
		}
	}
}

void APacNode::DrawLinkConnection( APacLink* Link, FVector AlternateDirection)
{
	if(Link)
	{

		if((Link->Head1 && Link->Head1 == this )||(Link->Head2 && Link->Head2 == this ))
		{
			DrawDebugLine(GetWorld(),GetTransform().GetLocation(),Link->GetTransform().GetLocation(),FColor::Green,true,-1,0,4);
		}
		else
		{
			DrawDebugLine(GetWorld(),GetTransform().GetLocation(),Link->GetTransform().GetLocation(),FColor::Red,true,-1,0,4);
		}
	}
	else
	{
		DrawDebugPoint(GetWorld(),GetTransform().GetLocation()+ 10* AlternateDirection,10,FColor::White,true);
	}
}

void APacNode::Assign(APacMazePawn* PacMazePawn)
{
	Super::Assign(PacMazePawn);
	
}

void APacNode::DrawGizmos()
{
	Super::DrawGizmos();

	DrawLinkConnection(UpLink,MazeDirectionToVector(Up));
	DrawLinkConnection(LeftLink,MazeDirectionToVector(Left));
	DrawLinkConnection(RightLink,MazeDirectionToVector(Right));
	DrawLinkConnection(BottomLink,MazeDirectionToVector(Down));

	DrawDebugPoint(GetWorld(),GetTransform().GetLocation() ,8,bSpawnPellets?FColor::Yellow : FColor::White,true);
	
	
}



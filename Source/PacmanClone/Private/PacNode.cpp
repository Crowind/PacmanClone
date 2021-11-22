// Fill out your copyright notice in the Description page of Project Settings.


#include "PacNode.h"

#include "DrawDebugHelpers.h"
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
	
}

void APacNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	for (APacMazePawn* PacMazePawn : CurrentlyHandledPacPawns)
	{
		
		PacMazePawn->GetMovementComponent()->StopMovementImmediately();

		
		switch (PacMazePawn->GetDisplayedDirection().GetValue())
		{
		case Down:
			{
				if(BottomLink)
				{
					CurrentlyHandledPacPawns.Remove(PacMazePawn);
					BottomLink->Assign(PacMazePawn,Down);
				}
				break;
			}
		case Up:
			{
				if(UpLink)
				{
					CurrentlyHandledPacPawns.Remove(PacMazePawn);
					UpLink->Assign(PacMazePawn,Up);
				}
				break;
			}
		case Left:
			{
				if(Left)
				{
					CurrentlyHandledPacPawns.Remove(PacMazePawn);
					LeftLink->Assign(PacMazePawn,Left);
				}
				break;
			}
		case Right:
			{
				if(RightLink)
				{
					CurrentlyHandledPacPawns.Remove(PacMazePawn);
					RightLink->Assign(PacMazePawn,Right);
				}
				break;
			}
		default:
			{
				GEngine->AddOnScreenDebugMessage(-1,5,FColor::Orange,TEXT("wtf"));

				break;
			}
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

	DrawLinkConnection(UpLink,FVector::LeftVector);
	DrawLinkConnection(LeftLink,FVector::BackwardVector);
	DrawLinkConnection(RightLink,FVector::ForwardVector);
	DrawLinkConnection(BottomLink,FVector::RightVector);

	DrawDebugPoint(GetWorld(),GetTransform().GetLocation() ,8,bSpawnPellets?FColor::Yellow : FColor::White,true);
	
	
}



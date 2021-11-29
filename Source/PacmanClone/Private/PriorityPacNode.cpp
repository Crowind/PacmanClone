// Fill out your copyright notice in the Description page of Project Settings.


#include "PriorityPacNode.h"


void APriorityPacNode::Tick(float DeltaSeconds)
{

	const int HandledPawns = CurrentlyHandledPacPawns.Num();
	
	for(int i = HandledPawns-1; i>=0;i--)
	{
		APacMazePawn* PacMazePawn = CurrentlyHandledPacPawns[i];
		if(PacMazePawn== nullptr)
		{
			return;
		}
		PacMazePawn->SetPacMovementActive(false);

		bool bAssigned = TryAssignPawnToDirection(PacMazePawn, PriorityDirection);
		if (!bAssigned)
		{
			bAssigned = TryAssignPawnToDirection(PacMazePawn, PacMazePawn->GetDisplayedDirection());
			if (!bAssigned)
			{
				TryAssignPawnToDirection(PacMazePawn, PacMazePawn->GetMovementDirection());
			}
		}
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPacLink.h"


void ATeleportPacLink::Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> EntranceDirection)
{

	//CurrentlyHandledPacPawns.Remove(PacMazePawn);
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Emerald,TEXT("Teleport"));
	PacMazePawn->SetPacMovementActive(true);
	mapping[EntranceDirection]->Assign(PacMazePawn);
	
}

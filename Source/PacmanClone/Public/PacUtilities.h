// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazePawn.h"


TEnumAsByte<EMazeDirection> static Opposite(const TEnumAsByte<EMazeDirection>& Direction)
{
	switch (Direction) {
	case Down: return Up;
	case Right: return Left;
	case Up: return Down;
	case Left: return Right;
	default: return Direction ;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacLink.h"
#include "TeleportPacLink.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API ATeleportPacLink : public APacLink
{
	GENERATED_BODY()


	virtual void Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> entranceDirection) override;	

	virtual void BeginPlay() override;
};

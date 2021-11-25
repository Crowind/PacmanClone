// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazePawn.h"
#include "PacPerson.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacPerson : public APacMazePawn
{
	GENERATED_BODY()


	virtual void Tick(float DeltaSeconds) override;
	
};
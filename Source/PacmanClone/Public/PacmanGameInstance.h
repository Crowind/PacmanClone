// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PacmanGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API UPacmanGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int level=0;
	int score=0;
	int lives = 3;
	
};

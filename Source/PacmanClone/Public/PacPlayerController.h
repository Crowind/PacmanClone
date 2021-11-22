// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PacPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	explicit APacPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazePawn.h"
#include "PacScoreItem.h"
#include "Chaos/AABB.h"
#include "PacMazeZone.generated.h"


UCLASS()
class PACMANCLONE_API APacMazeZone : public AActor
{
	GENERATED_BODY()

public:	

	static bool bIsMazeActive;

	// Sets default values for this component's properties
	APacMazeZone();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bSpawnPellets;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(EditCondition= "bSpawnPellets"))
	TSubclassOf<APacScoreItem> ScoreSpawnType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor GizmoColor;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<APacMazePawn *> CurrentlyHandledPacPawns; 

	virtual void DrawGizmos();

	UFUNCTION(BlueprintCallable)
	virtual void Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> entranceDirection = Down);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
		
};

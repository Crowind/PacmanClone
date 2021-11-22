// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazeZone.h"
#include "PacLink.generated.h"

UCLASS()
class PACMANCLONE_API APacLink : public APacMazeZone
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacLink();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APacMazeZone* Head1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APacMazeZone* Head2;

	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EMazeDirection>,APacMazeZone*> mapping;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual void Tick(float DeltaSeconds) override;

	virtual void DrawGizmos() override;

	virtual void Assign(APacMazePawn* PacMazePawn, TEnumAsByte<EMazeDirection> entranceDirection);

	UFUNCTION(BlueprintCallable)
	virtual void TryAttach(APacMazeZone* NewHead);
	static float InverseLerp(float xx, float yy, float value);
	static float InverseLerp(FVector v1, FVector v2, FVector value);

	UFUNCTION(BlueprintCallable)
    virtual void MovePawns();
   
};

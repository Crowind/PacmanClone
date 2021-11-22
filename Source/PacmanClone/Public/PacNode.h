// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazeZone.h"
#include "PacLink.h"
#include "PacNode.generated.h"

UCLASS()
class PACMANCLONE_API APacNode : public APacMazeZone
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacNode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class APacLink* UpLink;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class APacLink* BottomLink;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class APacLink* LeftLink;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class APacLink* RightLink;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	void DrawLinkConnection(APacLink* Link,FVector AlternateDirection);

	
	virtual void Assign(APacMazePawn* PacMazePawn) override;
	
	virtual void DrawGizmos() override;

};

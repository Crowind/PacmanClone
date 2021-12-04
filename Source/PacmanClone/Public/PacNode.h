// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacMazeZone.h"
#include "PacLink.h"
#include "PacNode.generated.h"

struct FVertexAndIndex
{
	FVector Vertex;
	int Index;

	FVertexAndIndex(const FVector& Vector, float X)
	{
		Vertex = Vector;
		Index = X;
	};
	FVertexAndIndex()
	{
		Vertex=FVector::ZeroVector;
		Index= -1;
	};
};

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


	FVertexAndIndex Vertex_NE;
	FVertexAndIndex Vertex_NW;
	FVertexAndIndex Vertex_SE;
	FVertexAndIndex Vertex_SW;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool TryAssignPawnToDirection(APacMazePawn* PacMazePawn,TEnumAsByte<EMazeDirection> Direction);


public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	void DrawLinkConnection(APacLink* Link,FVector AlternateDirection);

	
	virtual void Assign(APacMazePawn* PacMazePawn) override;
	
	virtual void DrawGizmos() override;

};

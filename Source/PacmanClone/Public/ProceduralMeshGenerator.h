// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacNode.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMeshGenerator.generated.h"





UCLASS()
class PACMANCLONE_API AProceduralMeshGenerator : public AActor
{
	GENERATED_BODY()

	float IndexCount=0;
	UPROPERTY()
	TArray<APacNode*> VisitedNodes;
	
public:	
	// Sets default values for this actor's properties
	AProceduralMeshGenerator();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float TunnelHalfSize;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector Offset;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	APacNode* StartPacNode;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FVector> Vertices;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int> Triangles1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int> Triangles2;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int> Triangles3;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FVector2D> UVs1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FVector2D> UVs2;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FVector2D> UVs3;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void CreateVerticesAndTriangles(APacNode* PacNode);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

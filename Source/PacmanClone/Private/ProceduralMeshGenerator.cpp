// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshGenerator.h"

#include "TeleportPacLink.h"


// Sets default values
AProceduralMeshGenerator::AProceduralMeshGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AProceduralMeshGenerator::CreateVerticesAndTriangles(APacNode* PacNode)
{
	VisitedNodes.Add(PacNode);

	const FVector Center = PacNode->GetTransform().GetLocation();
	
	PacNode->Vertex_NW = FVertexAndIndex (Offset + Center + FVector(-TunnelHalfSize,-TunnelHalfSize,0),IndexCount++);
	PacNode->Vertex_NE = FVertexAndIndex (Offset + Center + FVector(TunnelHalfSize,-TunnelHalfSize,0), IndexCount++);
	PacNode->Vertex_SE = FVertexAndIndex (Offset + Center + FVector(TunnelHalfSize,TunnelHalfSize,0) , IndexCount++);
	PacNode->Vertex_SW = FVertexAndIndex (Offset + Center + FVector(-TunnelHalfSize,TunnelHalfSize,0) ,IndexCount++);

	Vertices.Append({
		PacNode->Vertex_NW.Vertex,
		PacNode->Vertex_NE.Vertex,
		PacNode->Vertex_SE.Vertex,
		PacNode->Vertex_SW.Vertex,
	});

	UVs1.Append({
		FVector2D(0,0),
		FVector2D(1,0),
		FVector2D(1,1),
		FVector2D(0,1),

	});

	float y = 1;
	float x = 1;

	if(PacNode->UpLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->UpLink);
		APacNode* Node = Cast<APacNode>(PacNode->UpLink->mapping[Up]);
		if(Teleport == nullptr)
		{
			
			y = (FVector::Distance(PacNode->GetActorLocation(),Node->GetActorLocation()) - 2*TunnelHalfSize)/ (2*TunnelHalfSize)  ;
		}
	}
	
	if(PacNode->LeftLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->LeftLink);
		APacNode* Node = Cast<APacNode>(PacNode->LeftLink->mapping[Left]);
		if(Teleport == nullptr)
		{
			
			x = (FVector::Distance(PacNode->GetActorLocation(),Node->GetActorLocation()) - 2*TunnelHalfSize)/ (2*TunnelHalfSize)  ;
		}
	}
	
	
	UVs2.Append({
		FVector2D(0,y),
		FVector2D(1,y),
		FVector2D(1,0),
		FVector2D(0,0),

	});
	
	UVs3.Append({
		FVector2D(x,0),
		FVector2D(0,0),
		FVector2D(0,1),
		FVector2D(x,1),

	});
	
	Triangles1.Append({
		PacNode->Vertex_SW.Index,
		PacNode->Vertex_NE.Index,
		PacNode->Vertex_NW.Index
	});
	Triangles1.Append({
		PacNode->Vertex_SW.Index,
		PacNode->Vertex_SE.Index,
		PacNode->Vertex_NE.Index
	});

	if(PacNode->BottomLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->BottomLink);
		
		APacNode* Node = Cast<APacNode>(PacNode->BottomLink->mapping[Down]);
			if(Teleport==nullptr){
			
				if(!VisitedNodes.Contains(Node))
				{
					CreateVerticesAndTriangles(Node);
				}
				Triangles2.Append({
					PacNode->Vertex_SW.Index,
					Node->Vertex_NW.Index,
					PacNode->Vertex_SE.Index
				});
				Triangles2.Append({
					Node->Vertex_NW.Index,
					Node->Vertex_NE.Index,
					PacNode->Vertex_SE.Index
				});
			
		}
		
	}
	if(PacNode->RightLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->RightLink);
		APacNode* Node = Cast<APacNode>(PacNode->RightLink->mapping[Right]);
		
		if(Teleport==nullptr){
			if(!VisitedNodes.Contains(Node))
			{
				CreateVerticesAndTriangles(Node);
			}
			Triangles3.Append({
				PacNode->Vertex_NE.Index,
				PacNode->Vertex_SE.Index,
				Node->Vertex_NW.Index
			});
			Triangles3.Append({
				PacNode->Vertex_SE.Index,
				Node->Vertex_SW.Index,
				Node->Vertex_NW.Index
			});
		}
	}
	if(PacNode->LeftLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->LeftLink);
		APacNode* Node = Cast<APacNode>(PacNode->LeftLink->mapping[Left]);
		if(!VisitedNodes.Contains(Node) && Teleport==nullptr)
		{
			CreateVerticesAndTriangles(Node);
		}
	}
	if(PacNode->UpLink)
	{
		ATeleportPacLink* Teleport = Cast<ATeleportPacLink>(PacNode->UpLink);
		APacNode* Node = Cast<APacNode>(PacNode->UpLink->mapping[Up]);
		if(!VisitedNodes.Contains(Node) && Teleport == nullptr)
		{
			CreateVerticesAndTriangles(Node);
			
		}
	}
	
	
}

void AProceduralMeshGenerator::DataIsReady_Implementation()
{
}

void AProceduralMeshGenerator::ComputeData()
{
	CreateVerticesAndTriangles(StartPacNode);

	DataIsReady();
}

// Called when the game starts or when spawned
void AProceduralMeshGenerator::BeginPlay()
{

	
	Super::BeginPlay();
}

// Called every frame
void AProceduralMeshGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


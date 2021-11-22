// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazePawn.h"

#include "GameFramework/PawnMovementComponent.h"


FVector* APacMazePawn::DirectionToVector(EMazeDirection Direction)
{
	switch (Direction)
	{
	case Down :
		{
			return new FVector(0,1,0);
			break;
		}
	case Left :
		{
			return new FVector(-1,0,0);
			break;
		}
	case Right :
		{
			return new FVector(1,0,0);
			break;
		}
	case Up :
		{
			return new FVector(0,-1,0);
			break;
		}
		
	}
	return nullptr;
}

APacMazePawn::APacMazePawn():Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DisplayedDirection = Left;
	
	
}

// Called when the game starts or when spawned
void APacMazePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APacMazePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector* DirectionVector = DirectionToVector(DisplayedDirection);
	
    AddMovementInput(*DirectionVector,Speed);
	
	delete(DirectionVector);
	
	
}

// Called to bind functionality to input
void APacMazePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Up",IE_Pressed,this,&APacMazePawn::GoUp);
	PlayerInputComponent->BindAction("Down",IE_Pressed,this,&APacMazePawn::GoDown);
	PlayerInputComponent->BindAction("Left",IE_Pressed,this,&APacMazePawn::GoLeft);
	PlayerInputComponent->BindAction("Right",IE_Released,this,&APacMazePawn::GoRight);

}

void APacMazePawn::SetDisplayDirection_Implementation(const EMazeDirection Direction)
{
	this->DisplayedDirection = Direction;
}

TEnumAsByte<EMazeDirection> APacMazePawn::GetDisplayedDirection()
{
	return DisplayedDirection;
}

void APacMazePawn::SetMovementDirection(EMazeDirection Direction)
{
	GetMovementComponent()->StopMovementImmediately();
	MovementDirection=Direction;
}

TEnumAsByte<EMazeDirection> APacMazePawn::GetMovementDirection()
{
	return MovementDirection;
}

void APacMazePawn::GoUp()
{
	//GEngine->AddOnScreenDebugMessage(-1,2, FColor::Blue,TEXT("Up"));
	this->SetDisplayDirection(Up);
}
void APacMazePawn::GoDown()
{
	this->SetDisplayDirection(Down);
}
void APacMazePawn::GoLeft()
{
	this->SetDisplayDirection(Left);
}
void APacMazePawn::GoRight()
{
	this->SetDisplayDirection(Right);
}


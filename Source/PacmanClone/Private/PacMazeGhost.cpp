// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeGhost.h"

#include "AIController.h"
#include "PacmanGameMode.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

APacMazeGhost::APacMazeGhost(const FObjectInitializer& ObjectInitializer): APacMazePawn(ObjectInitializer)
{

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper FlipBook Component"));
	PaperFlipbookComponent->SetupAttachment(GetCapsuleComponent());
	
	PaperFlipbookComponent->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270,0,0)));
	PaperFlipbookComponent->SetRelativeLocation(FVector(0,0,0));
	PaperFlipbookComponent->SetWorldScale3D(FVector::OneVector*4);
	
}

void APacMazeGhost::FlipDirection()
{
	SetDisplayDirection(Opposite(GetMovementDirection()));
}

void APacMazeGhost::EnterFrightenedState()
{
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsFloat(FName("FrightenedTimeStamp"),GetWorld()->TimeSeconds);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsEnum(FName("GhostCurrentState"),EPacGhostState::Frightened);
	FlipDirection();
	
}

void APacMazeGhost::OnExitFrightenedState()
{
	
}

UPaperFlipbookComponent* APacMazeGhost::GetPaperFlipbookComponent()
{
	return PaperFlipbookComponent;
}

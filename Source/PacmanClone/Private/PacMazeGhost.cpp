// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeGhost.h"

#include "PacUtilities.h"
#include "Components/CapsuleComponent.h"

// APacMazeGhost::APacMazeGhost()
// {
// 	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper FlipBook Component"));
// 	PaperFlipbookComponent->SetupAttachment(GetCapsuleComponent());
// 	
// 	PaperFlipbookComponent->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270,0,0)));
// 	PaperFlipbookComponent->SetRelativeLocation(FVector(0,0,0));
// 	PaperFlipbookComponent->SetWorldScale3D(FVector::OneVector*4);
// 	
// }

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
	SetMovementDirection(Opposite(GetMovementDirection()));
}

UPaperFlipbookComponent* APacMazeGhost::GetPaperFlipbookComponent()
{
	return PaperFlipbookComponent;
}

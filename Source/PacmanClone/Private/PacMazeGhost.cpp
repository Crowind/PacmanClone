// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMazeGhost.h"

#include "AIController.h"
#include "PacLink.h"
#include "PacMazeZone.h"
#include "PacUtilities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

APacMazeGhost::APacMazeGhost(const FObjectInitializer& ObjectInitializer): APacMazePawn(ObjectInitializer)
{

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper FlipBook Component"));
	PaperFlipbookComponent->SetupAttachment(GetCapsuleComponent());
	
	PaperFlipbookComponent->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270,0,0)));
	PaperFlipbookComponent->SetRelativeLocation(FVector(0,0,0));
	PaperFlipbookComponent->SetWorldScale3D(FVector::OneVector*4);

	
	EatenAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Eaten Audio Component"));
	EatenAudioComponent->SetupAttachment(RootComponent);
	
	
}

void APacMazeGhost::FlipDirection()
{
	SetMovementDirection(Opposite(GetMovementDirection()));

	auto Link = Cast<APacLink>(CurrentZone);

	if(Link!= nullptr && Link->bFlipGhostSteering)
	{
		FlipSteering();
	}
	
}

void APacMazeGhost::EnterFrightenedState()
{
	EPacGhostState state = static_cast<EPacGhostState>(Cast<AAIController>(GetController())->GetBlackboardComponent()->GetValueAsEnum(FName("GhostCurrentState")));

	if(state == Eaten)
	{
		return;
	}
	
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsFloat(FName("FrightenedTimeStamp"),GetWorld()->TimeSeconds);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsEnum(FName("GhostCurrentState"),EPacGhostState::Frightened);

	if (bOutOfHouse)
	{
		FlipDirection();
	}
	
}

void APacMazeGhost::OnExitFrightenedState()
{
	
}

void APacMazeGhost::SetSteering(bool bCond)
{
	EPacGhostState state = static_cast<EPacGhostState>(Cast<AAIController>(GetController())->GetBlackboardComponent()->GetValueAsEnum(FName("GhostCurrentState")));

	if(state == Eaten)
	{
		return;
	}
	bCanSteer= bCond;
}

TEnumAsByte<EMazeDirection> APacMazeGhost::GetDisplayedDirection()
{
	if(bCanSteer || !bOutOfHouse){
		return Super::GetDisplayedDirection();
	}
	return GetMovementDirection();
}


void APacMazeGhost::FlipSteering()
{

	EPacGhostState state = static_cast<EPacGhostState>(Cast<AAIController>(GetController())->GetBlackboardComponent()->GetValueAsEnum(FName("GhostCurrentState")));

	if(state == Eaten)
	{
		return;
	}
	
	bCanSteer = !bCanSteer;
}

void APacMazeGhost::BeginPlay()
{
	Super::BeginPlay();
	EatenAudioComponent->Stop();
}

void APacMazeGhost::GetEaten()
{
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsEnum(FName("GhostCurrentState"),EPacGhostState::Eaten);
	EatenAudioComponent->Play();
}

void APacMazeGhost::InitGhost_Implementation(bool respawn)
{
}


UPaperFlipbookComponent* APacMazeGhost::GetPaperFlipbookComponent()
{
	return PaperFlipbookComponent;
}

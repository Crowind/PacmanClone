// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostsSoundsPlayer.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "EngineUtils.h"
#include "PacmanGameMode.h"
#include "PacMazeGhost.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AGhostsSoundsPlayer::AGhostsSoundsPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	AudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGhostsSoundsPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostsSoundsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bFrightened = false;
	
	for (TActorIterator<APacMazeGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AAIController* aiController = Cast<AAIController>(ActorItr->GetController());
		if(aiController==nullptr || aiController->BrainComponent == nullptr || !aiController->BrainComponent->IsRunning() )
		{
			continue;
		}
		EPacGhostState PacGhostState = static_cast<EPacGhostState>(aiController->GetBlackboardComponent()->GetValueAsEnum(FName("GhostCurrentState")));

		bFrightened = bFrightened || (PacGhostState==Frightened || PacGhostState==FrightenedEnding);
	}
	AudioComponent->SetBoolParameter(FName("Frightened"),bFrightened);
	
	if(bFrightened)
	{
		AudioComponent->SetPitchMultiplier(1);
	}
	else
	{
		int anger = Cast<APacmanGameMode>(GetWorld()->GetAuthGameMode())->BlinkyAngryLevel();
		float pitch = anger ==2? 2: anger ==1? 1.5 :1;
		AudioComponent->SetPitchMultiplier(pitch);
		
	}
	
	
}


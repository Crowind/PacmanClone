// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGameManager.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "EngineUtils.h"
#include "PacmanGameMode.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APacGameManager::APacGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Start Audio Component"));

	StartAudioComponent->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void APacGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	APacMazeZone::bIsMazeActive=false;
	
	Cast<APacmanGameMode>(GetWorld()->GetAuthGameMode())->GameManager = this;
	
	Player = Cast<APacPerson>(UGameplayStatics::GetActorOfClass(AActor::GetWorld(),APacPerson::StaticClass()));

	
	for (APacMazeGhost* Ghost : Ghosts)
	{
		Ghost->SetPacMovementActive(false);
	}
	Player->SetPacMovementActive(false);
	GhostsSoundsPlayer->AudioComponent->Stop();

	PlayIntro();
}

// Called every frame
void APacGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APacGameManager::PlayIntro()
{
	
	float duration = StartAudioComponent->IsPlaying() ? StartAudioComponent->Sound->Duration+1 : 2.f;
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &APacGameManager::InitMaze,duration , false,duration);


	Player->SetActorLocation(PlayerStartNode->GetTransform().GetLocation());
	Player->InitPacPersonAppereance();
}

void APacGameManager::InitMaze()
{
	if(ReadyActor!=nullptr)
	{
		ReadyActor->Destroy();
	}

	APacMazeZone::bIsMazeActive=true;
	Cast<APacmanGameMode>(GetWorld()->GetAuthGameMode())->ResetTime();
	
	Player->InitPacPerson();
	PlayerStartNode->Assign(Player);
	for (APacMazeGhost* Ghost : Ghosts)
	{
		Ghost->InitGhost(bRespawning);
	}
	GhostsSoundsPlayer->AudioComponent->Play();

	APacMazeZone::bIsMazeActive=true;
}

void APacGameManager::StopMaze()
{
	APacMazeZone::bIsMazeActive=false;
	for (APacMazeGhost* Ghost : Ghosts)
	{
		Ghost->SetActorLocation(FVector(100000,100000,0));
		Ghost->SetPacMovementActive(false);
		Cast<AAIController>(Ghost->GetController())->GetBrainComponent()->StopLogic("Reset");
		Ghost->CurrentZone->CurrentlyHandledPacPawns.Remove(Ghost);
		Ghost->EatenAudioComponent->Stop();
	}
	Player->SetPacMovementActive(false);
	Player->CurrentZone->CurrentlyHandledPacPawns.Remove(Player);
	GhostsSoundsPlayer->AudioComponent->Stop();
	
}


void APacGameManager::ResetGame() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APacGameManager::Death(bool reset)
{
	StopMaze();
	Player->PlayDeath();

	if(reset)
	{
		GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &APacGameManager::ResetGame, Player->DeathAudioComponent->Sound->Duration+1, false,Player->DeathAudioComponent->Sound->Duration+1 );
		
	}
	else
	{
		bRespawning=true;
		GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &APacGameManager::PlayIntro, Player->DeathAudioComponent->Sound->Duration+1, false, Player->DeathAudioComponent->Sound->Duration+1);
	}
}




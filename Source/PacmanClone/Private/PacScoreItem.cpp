// Fill out your copyright notice in the Description page of Project Settings.


#include "PacScoreItem.h"

#include "Pacman.h"
#include "PacmanGameMode.h"
#include "PacMazePawn.h"
#include "Kismet/GameplayStatics.h"

void APacScoreItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APacScoreItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void APacScoreItem::Consume()
{

	APacmanGameMode* GameMode = Cast< APacmanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->AddPoints(Score);
	Destroy();
	
}

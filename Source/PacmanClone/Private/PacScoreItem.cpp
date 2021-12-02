// Fill out your copyright notice in the Description page of Project Settings.


#include "PacScoreItem.h"

#include "PacmanGameMode.h"
#include "Kismet/GameplayStatics.h"


int APacScoreItem::WinItemCount;

APacScoreItem* APacScoreItem::firstItem;

void APacScoreItem::BeginPlay()
{
	Super::BeginPlay();

	if(firstItem==nullptr)
	{
		firstItem=this;
		WinItemCount=0;
	}
	
	if(bWinRequisite)
	{
		WinItemCount++;
	}
}

void APacScoreItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

int APacScoreItem::GetWinItemsCount()
{
	return WinItemCount;
}

void APacScoreItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(EndPlayReason!=EEndPlayReason::Destroyed)
	{
		firstItem=nullptr;
		
	}
	
	Super::EndPlay(EndPlayReason);
}

void APacScoreItem::Consume_Implementation()
{
	APacmanGameMode* GameMode = Cast< APacmanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->AddPoints(Score);
	if(bWinRequisite)
	{
		WinItemCount--;
	}
	Destroy();
	
}



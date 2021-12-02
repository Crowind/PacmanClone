// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathManager.h"
#include "Components/AudioComponent.h"

// Sets default values
ADeathManager::ADeathManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Death Audio Component"));

	DeathAudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADeathManager::BeginPlay()
{
	Super::BeginPlay();
	DeathAudioComponent->Stop();
}

// Called every frame
void ADeathManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



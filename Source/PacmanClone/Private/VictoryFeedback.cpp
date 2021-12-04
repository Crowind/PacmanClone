// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryFeedback.h"

#include "Components/AudioComponent.h"

// Sets default values
AVictoryFeedback::AVictoryFeedback()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	VictoryAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Victory Audio Component"));
	VictoryAudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AVictoryFeedback::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVictoryFeedback::Victory_Implementation()
{
}

// Called every frame
void AVictoryFeedback::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


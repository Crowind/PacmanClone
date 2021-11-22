// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APacman::APacman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void APacman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



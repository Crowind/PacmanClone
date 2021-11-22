// Fill out your copyright notice in the Description page of Project Settings.


#include "PacPlayerCameraManager.h"

#include "EmptyActor.h"

APacPlayerCameraManager::APacPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsOrthographic = true;

	DefaultAspectRatio = 1.777778f;
	bDefaultConstrainAspectRatio = true;
	DefaultOrthoWidth = 1777;
	APacPlayerCameraManager::SetActorHiddenInGame(false);
}

void APacPlayerCameraManager::BeginPlay()
{
	if (bIsFixedPOV)
	{
		const FActorSpawnParameters SpawnInfo;
		AEmptyActor* DestinationActor = GetWorld()->SpawnActor<AEmptyActor>(
			FVector(FixedLocation), FRotator(FixedRotation), SpawnInfo);

		//DestinationActor->SetActorLabel(TEXT("cameraSpawnActor"));
		DestinationActor->SetActorHiddenInGame(true);

		SetViewTarget(DestinationActor);
	}
	Super::BeginPlay();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "PacPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API APacPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	UPROPERTY( Category= PacCamera , EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool bIsFixedPOV = true;

	UPROPERTY( Category= PacCamera , EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true", EditCondition = "bIsFixedPov"))
	FVector FixedLocation = FVector(0,0,620);
	
	
	UPROPERTY( Category= PacCamera , EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true", EditCondition = "bIsFixedPov"))
	FRotator FixedRotation = FRotator::MakeFromEuler(FVector(0,-90,270));
	
	APacPlayerCameraManager(const FObjectInitializer& ObjectInitializer);


	virtual void BeginPlay() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryFeedback.generated.h"

UCLASS()
class PACMANCLONE_API AVictoryFeedback : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryFeedback();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UAudioComponent* VictoryAudioComponent;

	UFUNCTION(BlueprintNativeEvent)
	void Victory();
	
};

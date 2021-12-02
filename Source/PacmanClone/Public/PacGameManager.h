// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostsSoundsPlayer.h"
#include "PacMazeGhost.h"
#include "PacNode.h"
#include "PacPerson.h"
#include "GameFramework/Actor.h"
#include "PacGameManager.generated.h"

UCLASS()
class PACMANCLONE_API APacGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacGameManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayIntro();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	APacPerson* Player;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APacNode* PlayerStartNode;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<APacMazeGhost*> Ghosts;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AGhostsSoundsPlayer* GhostsSoundsPlayer;
	
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UAudioComponent* StartAudioComponent;
	FTimerHandle DeathTimerHandle;
	bool bRespawning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ReadyActor;

	UFUNCTION(BlueprintCallable)
	void InitMaze();
	
	UFUNCTION(BlueprintCallable)
	void StopMaze();
	void ResetGame() const;

	UFUNCTION(BlueprintCallable)
	void Death(bool reset = false);
};

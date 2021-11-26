// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacMazePawn.generated.h"
class APacMazeZone;
UENUM(BlueprintType)
enum EMazeDirection {Down,Right,Up,Left};


UCLASS()
class PACMANCLONE_API APacMazePawn : public ACharacter
{
	GENERATED_BODY()

private:
	
	UPROPERTY(Category=MazePawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TEnumAsByte<EMazeDirection> DisplayedDirection;
	
	UPROPERTY(Category=MazePawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TEnumAsByte<EMazeDirection> MovementDirection;
	
	
	UPROPERTY(Category=MazePawn, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float DefaultSpeed = 200;
	
	UPROPERTY(Category=MazePawn, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float Speed = 200;
	
	UPROPERTY(Category=MazePawn,VisibleAnywhere)
	bool bPacMovementEnabled;


public:

	UPROPERTY(Category=MazePawn,VisibleAnywhere,BlueprintReadWrite)
	APacMazeZone* CurrentZone;

	static FVector* DirectionToVector(EMazeDirection Direction);
	
	// Sets default values for this pawn's properties

	explicit APacMazePawn(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PacMove(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
	void SetDisplayDirection(EMazeDirection Direction);
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EMazeDirection> GetDisplayedDirection();

	UFUNCTION(BlueprintCallable)
	void SetMovementDirection(EMazeDirection Direction);
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EMazeDirection> GetMovementDirection();

	UFUNCTION(BlueprintCallable)
	void SetPacMovementActive(bool active);

	UFUNCTION(BlueprintCallable)
	bool GetPacMovementActive();

	
	UFUNCTION(BlueprintCallable)
	void GoUp();
	UFUNCTION(BlueprintCallable)
	void GoDown();
	UFUNCTION(BlueprintCallable)
	void GoLeft();
	UFUNCTION(BlueprintCallable)
	void GoRight();
};

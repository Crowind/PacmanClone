// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacMazePawn.generated.h"
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
	float Speed = 1;

	
public:

	static FVector* DirectionToVector(EMazeDirection Direction);
	
	// Sets default values for this pawn's properties

	explicit APacMazePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	void GoUp();
	UFUNCTION(BlueprintCallable)
	void GoDown();
	UFUNCTION(BlueprintCallable)
	void GoLeft();
	UFUNCTION(BlueprintCallable)
	void GoRight();
};

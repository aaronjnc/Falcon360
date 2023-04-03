// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VizParentPawn.generated.h"

struct FInputActionValue;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class FALCON360_API AVizParentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVizParentPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void RotatePlayer(const FInputActionValue& Value);

	UFUNCTION()
	void ShootLeft();

	UFUNCTION()
	void ShootRight();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RightShootAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftShootAction;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;

	UPROPERTY()
	APlayerController* PlayerController;

};

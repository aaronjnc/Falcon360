// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Pawn.h"
#include "VizParentPawn.generated.h"

class UTurret;
struct FInputActionValue;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UBoxComponent;

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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:

	UFUNCTION()
	void RotatePlayer(const FInputActionValue& Value);

	UFUNCTION()
	void ShootLeft();

	UFUNCTION()
	void ShootRight();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UTurret* TurretComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* LaserHitBox;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* LeftBlaster;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* RightBlaster;

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

	UPROPERTY(EditAnywhere, Category = "Blasters")
	FDataTableRowHandle BlasterInfo;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;
	
	UPROPERTY()
	float Health;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxShield;

	UPROPERTY()
	float Shield;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StructClass.h"
#include "EnemyShip.generated.h"

class AFlightPoint;
class UTurret;
class UFloatingPawnMovement;
class ULeadShip;
class AEnemyShip;

UCLASS()
class FALCON360_API AEnemyShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void SetShipType(bool IsLeadShip, FEnemyShips ShipInfo, ULeadShip* NewLeadShip);
	
	void SetDestination(FVector Destination);

	UFUNCTION(BlueprintCallable)
	void GetNextPoint();

	void BeginAttack();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UFUNCTION(BlueprintCallable)
	void RotateTowardsDestination();

	UFUNCTION(BlueprintCallable)
	void SetForwardVelocity();

	UFUNCTION(BlueprintCallable)
	void AimTurret();

	UFUNCTION(BlueprintCallable)
	void StartShooting();

	UFUNCTION(BlueprintCallable)
	bool CanShoot();

	UFUNCTION(BlueprintCallable)
	bool IsAttacking();

	UFUNCTION(BlueprintCallable)
	bool CanGoToNextPoint();

	UFUNCTION(BlueprintCallable)
	bool CanDivertAttack();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* LeftBlaster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RightBlaster;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UTurret* TurretComponent;
	
	UPROPERTY(BlueprintReadOnly)
	FVector NextPointPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Overall")
	float RotateSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Overall")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Overall")
	float DivertAttackDistance;

	UPROPERTY(BlueprintReadOnly)
	bool bAttacking;

	UPROPERTY(BlueprintReadOnly)
	bool bShooting;

private:

	UFUNCTION()
	void ContinueShooting();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	float Health;

	UPROPERTY()
	float MaxShield;

	UPROPERTY()
	float Shield;

	UPROPERTY()
	float FireRate;

	UPROPERTY()
	bool bLeadShip;

	UPROPERTY()
	ULeadShip* LeadShip;

	UPROPERTY()
	float AngleDiff;

	FTimerDelegate TimerDelegate;

	FTimerHandle TimerHandle;
};

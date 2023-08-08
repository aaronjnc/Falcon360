// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "VizParentPawn.generated.h"

class UTurret;
struct FInputActionValue;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UBoxComponent;
class AVizParentPawn;

USTRUCT()
struct FBlasterInfo
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;

	bool bShooting;

	typedef void (AVizParentPawn::* CallBackFunction )(void);

	CallBackFunction PtrFunction;
	
};

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

	void NewWave(int Wave);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWave(int Wave);

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthAndShield(float NewHealth, float NewShield);

	UFUNCTION(BlueprintImplementableEvent)
	void EndScreen();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float RotationModifier;

private:

	UFUNCTION()
	void RotatePlayer(const FInputActionValue& Value);

	UFUNCTION()
	void ShootLeft();

	UFUNCTION()
	void StopShootingLeft();

	UFUNCTION()
	void ShootRight();

	UFUNCTION()
	void StopShootingRight();

	UFUNCTION()
	void ContinueShooting(int i);

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

	UPROPERTY()
	float FireRate;

	FTimerDelegate TimerDelegate;

	UPROPERTY()
	TArray<FBlasterInfo> BlasterInfos;

};

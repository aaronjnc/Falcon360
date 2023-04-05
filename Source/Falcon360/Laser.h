// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Laser.generated.h"

class AFalcon360GameModeBase;
class UProjectileMovementComponent;

UCLASS()
class FALCON360_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLaserType(FName LaserName);

private:

	UFUNCTION()
	void DestroyLaser();

	UPROPERTY(EditAnywhere, Category = "Components")
	UNiagaraComponent* LaserComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* LaserCollider;

	UPROPERTY(EditAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
	float Damage;
	
	UPROPERTY()
	AFalcon360GameModeBase* GameModeBase;

	FTimerHandle LifetimeTimerHandle;

};

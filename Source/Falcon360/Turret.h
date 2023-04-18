// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TimerManager.h"
#include "Turret.generated.h"

USTRUCT()
struct FTurretInfo
{
	GENERATED_BODY()

	USceneComponent* SceneComponent;
	
};


class ALaser;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALCON360_API UTurret : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurret();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void SetTurretInfo(FDataTableRowHandle RowHandle, USceneComponent* LeftTurret, USceneComponent* RightTurret);
	
	// Called every frame
	UFUNCTION()
	void Shoot(bool bLeft);

private:

	UFUNCTION()
	void Fire(int index);

	UPROPERTY(EditAnywhere, Category = "Blasters")
	TSubclassOf<ALaser> LaserSubclass;

	UPROPERTY()
	FDataTableRowHandle TableRow;
	
	UPROPERTY()
	float DelayTime;

	UPROPERTY()
	TArray<FTurretInfo> TurretInfos;

	FTimerDelegate TimerDelegate;
		
};

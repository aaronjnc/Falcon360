// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Turret.generated.h"


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
	// Called every frame
	UFUNCTION()
	void Shoot(FVector Location, FRotator Direction);

	UPROPERTY(EditAnywhere, Category = "Blasters")
	TSubclassOf<ALaser> LaserSubclass;

	UPROPERTY(EditAnywhere, Category = "Blasters")
	FDataTableRowHandle TableRow;
		
};

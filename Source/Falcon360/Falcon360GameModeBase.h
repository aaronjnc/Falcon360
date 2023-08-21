// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "StructClass.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Falcon360GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FALCON360_API AFalcon360GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UNiagaraSystem* GetNiagaraSystem(FName BlasterName) const;
	float GetDamage(FName BlasterName) const;
	float GetTime(FName BlasterName) const;
	float GetSpeed(FName BlasterName) const;
	TEnumAsByte<ECollisionChannel> GetCollisionChannel(FName BlasterName) const;
	
private:
	UPROPERTY(EditAnywhere, Category = "DataTables")
	UDataTable* BlastersTable;
};

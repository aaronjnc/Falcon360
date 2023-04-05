// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NiagaraFunctionLibrary.h"
#include "StructClass.generated.h"

USTRUCT(BlueprintType)
struct FBlasters : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* BlasterEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	
};

/**
 * 
 */
class FALCON360_API StructClass
{
public:
	StructClass();
	~StructClass();
};

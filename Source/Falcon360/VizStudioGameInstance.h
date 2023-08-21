// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VizStudioGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALCON360_API UVizStudioGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		ULocalPlayer * RequestLocalPlayer(int32 ControllerId, FString& OutError, bool bSpawnActor);
};

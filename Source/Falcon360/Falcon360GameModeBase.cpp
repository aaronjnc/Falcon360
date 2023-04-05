// Copyright Epic Games, Inc. All Rights Reserved.


#include "Falcon360GameModeBase.h"
#include "StructClass.h"

UNiagaraSystem* AFalcon360GameModeBase::GetNiagaraSystem(FName BlasterName) const
{
	return DataTable->FindRow<FBlasters>(BlasterName, "")->BlasterEffect;
}

float AFalcon360GameModeBase::GetDamage(FName BlasterName) const
{
	return DataTable->FindRow<FBlasters>(BlasterName, "")->Damage;
}

float AFalcon360GameModeBase::GetTime(FName BlasterName) const
{
	return DataTable->FindRow<FBlasters>(BlasterName, "")->Time;
}

float AFalcon360GameModeBase::GetSpeed(FName BlasterName) const
{
	return DataTable->FindRow<FBlasters>(BlasterName, "")->Speed;
}

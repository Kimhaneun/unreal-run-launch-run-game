// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.generated.h"

UCLASS()
class RUNLAUNCHRUN_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(FName("WeaponData"), GetFName());
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Durability")
	float Durability;

};

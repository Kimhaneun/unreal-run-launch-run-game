// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"Weapon/WeaponBase.h"
#include "ProjectOneHand.generated.h"

UCLASS()
class RUNLAUNCHRUN_API AProjectOneHand : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectOneHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual EWeaponType GetWeaponType() const override { return EWeaponType::OneHand; }

};

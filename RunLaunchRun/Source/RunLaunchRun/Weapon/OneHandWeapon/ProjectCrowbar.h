// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/OneHandWeapon/ProjectOneHand.h"
#include "ProjectCrowbar.generated.h"

/**
 * 
 */
UCLASS()
class RUNLAUNCHRUN_API AProjectCrowbar : public AProjectOneHand
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectCrowbar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// virtual void InteractInput(AActor* Interactor) override;

	virtual FText GetInteractionText() const override;

};

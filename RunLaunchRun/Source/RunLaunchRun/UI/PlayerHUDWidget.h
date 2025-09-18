// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNLAUNCHRUN_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UMessageWidget> WBP_NoWeaponMassage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UMessageWidget> WBP_WeaponDurabilityMassage;

};

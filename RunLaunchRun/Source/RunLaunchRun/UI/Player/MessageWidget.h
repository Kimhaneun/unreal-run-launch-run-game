// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

UCLASS()
class RUNLAUNCHRUN_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMessageWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION()
	void PlayFadeInAnimation();

	UFUNCTION()
	void PlayFadeOutAnimation();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeInAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeOutAnimation;

};

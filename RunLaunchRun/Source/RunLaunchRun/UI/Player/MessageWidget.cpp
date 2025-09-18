// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/MessageWidget.h"

UMessageWidget::UMessageWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMessageWidget::PlayFadeInAnimation()
{
	if (FadeInAnimation == nullptr)
	{
		return;
	}

	PlayAnimation(FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);

}

void UMessageWidget::PlayFadeOutAnimation()
{
	if (FadeOutAnimation == nullptr)
	{
		return;
	}

	PlayAnimation(FadeOutAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);

}

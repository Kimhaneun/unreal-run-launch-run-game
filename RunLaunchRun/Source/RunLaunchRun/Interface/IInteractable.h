// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUNLAUNCHRUN_API IIInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 추후 AI를 개발할 경우, 인터페이스 분리를 고려할 수 있다.
	// (단, 해당 코드는 ISP를 위반하지 않는다.)
	virtual void InteractInput(AActor* Interactor) = 0;
	virtual bool CanInteract() const { return true; }
	virtual FText GetInteractionText() const = 0;

};

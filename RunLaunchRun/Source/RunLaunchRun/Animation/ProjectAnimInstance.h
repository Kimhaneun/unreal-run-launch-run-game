// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ProjectAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RUNLAUNCHRUN_API UProjectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public: 
	UProjectAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ACharacter> Character;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float HorizontalSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float VerticalSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsMovingHorizontally = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsMovingVertically = false;

	UPROPERTY(BlueprintReadOnly, Category = "Jump")
	bool bIsFalling = false;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bIsCrouched = false;

};

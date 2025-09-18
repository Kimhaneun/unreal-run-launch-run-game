// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ProjectAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UProjectAnimInstance::UProjectAnimInstance()
{
}

void UProjectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UProjectAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
	{
		return;
	}

	if (MovementComponent == nullptr)
	{
		return;
	}

	Velocity = MovementComponent->Velocity;

	HorizontalSpeed = Velocity.Size2D();
	VerticalSpeed = Velocity.Z;

	const bool bHasAcceleration = MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;

	bIsMovingHorizontally = (HorizontalSpeed > KINDA_SMALL_NUMBER) && bHasAcceleration;
	bIsMovingVertically = (VerticalSpeed > KINDA_SMALL_NUMBER) && bHasAcceleration;

	bIsFalling = MovementComponent->IsFalling();

	bIsCrouched = MovementComponent->IsCrouching();

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{

}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

bool UWeaponComponent::EquipWeapon(AWeaponBase* NewWeapon, FName SocketName)
{
	if (NewWeapon == nullptr || EquippedWeapon)
	{
		return false;
	}

	auto* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter == nullptr)
	{
		return false;
	}

	NewWeapon->AttachToCharacter(OwnerCharacter, SocketName);
	EquippedWeapon = NewWeapon;

	return true;

}

void UWeaponComponent::UnequipWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromCharacter();
		EquippedWeapon = nullptr;
	}

}

void UWeaponComponent::DropWeaponBehindCharacter()
{
	if (EquippedWeapon == nullptr)
	{
		return;
	}

	if (auto* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		FVector BackDirection = OwnerCharacter->GetActorForwardVector();
		FVector DropLocation = OwnerCharacter->GetActorLocation() + BackDirection * 100.0f;
		FRotator DropRotation = OwnerCharacter->GetActorRotation();

		EquippedWeapon->DropAtLocation(DropLocation, DropRotation);
		EquippedWeapon = nullptr;
	}

}
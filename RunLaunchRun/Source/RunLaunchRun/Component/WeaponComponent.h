// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMessageFadeInDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMessageFadeOutDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNLAUNCHRUN_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool EquipWeapon(class AWeaponBase* NewWeapon, FName SocketName = "WeaponSocket");
	void UnequipWeapon();
	void DropWeaponBehindCharacter();

	TObjectPtr<class AWeaponBase> GetEquippedWeapon() const { return EquippedWeapon; }

	FOnMessageFadeInDelegate OnMessageFadeInDelegate;
	FOnMessageFadeOutDelegate OnMessageFadeOutDelegate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class AWeaponBase> EquippedWeapon;

};

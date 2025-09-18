// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectCharacterBase.h"
#include "Component/WeaponComponent.h" 
#include "Data/Weapon/WeaponData.h"

// Sets default values
AProjectCharacterBase::AProjectCharacterBase()
{
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

}

// Called when the game starts or when spawned
void AProjectCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProjectCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Executes the given callback after a delay in seconds
void AProjectCharacterBase::ExecuteAfterDelay(float DelayTime, TFunction<void()> Callback, FTimerHandle& OutHandle)
{
	if (Callback == nullptr)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(OutHandle, [Callback]() { Callback(); }, DelayTime, false);

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/OneHandWeapon/ProjectCrowbar.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/Weapon/WeaponData.h"

AProjectCrowbar::AProjectCrowbar()
{
	static ConstructorHelpers::FObjectFinder<UWeaponData> WeaponDataReference(TEXT("/Script/RunLaunchRun.WeaponData'/Game/Data/DA_WeaponData_Crowbar.DA_WeaponData_Crowbar'"));
	if (WeaponDataReference.Succeeded())
	{
		WeaponData = WeaponDataReference.Object;
	}

	float SphereRadius = 150.0f;
	SphereComponent->SetSphereRadius(SphereRadius);

	FVector MeshRelativeLocation(0.0f, 0.0f, -50.0f);
	MeshComponent->SetRelativeLocation(MeshRelativeLocation);

	FVector MeshRelativeScale(2.0f, 2.0f, 2.0f);
	MeshComponent->SetRelativeScale3D(MeshRelativeScale);

	float CapsuleRadius = 50.0f;
	CapsuleComponent->SetCapsuleHalfHeight(CapsuleRadius);

	FVector CapsuleRelativeLocation(0.0f, 0.0f, 50.0f);
	CapsuleComponent->SetRelativeLocation(CapsuleRelativeLocation);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshReference(TEXT("/Script/Engine.StaticMesh'/Game/Environment/Weapon/OneHand/Crowbar/Crowbar.Crowbar'"));
	if (MeshReference.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshReference.Object);
	}

}

void AProjectCrowbar::BeginPlay()
{
	Super::BeginPlay();

}

// void AProjectCrowbar::InteractInput(AActor* Interactor)
// {
// 	// 여기에 구현부
// 	Super::InteractInput(Interactor);
// 
// }

FText AProjectCrowbar::GetInteractionText() const
{
	return FText();

}

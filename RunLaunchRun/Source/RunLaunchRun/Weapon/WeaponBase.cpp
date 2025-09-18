// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "GameFramework/Character.h"
#include "Interface/IInteractableState.h"
#include "Interface/IAttack.h"
#include "Components/SphereComponent.h"
#include "Component/InteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/WeaponComponent.h"
#include "Data/Weapon/WeaponData.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SphereComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(MeshComponent);

	SphereComponent->SetCollisionProfileName(TEXT("Wpn_Collision_Unused"));
	MeshComponent->SetCollisionProfileName(TEXT("Wpn_Mesh_Unused"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnAttackOverlap);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::AttachToCharacter(ACharacter* Character, FName SocketName)
{
	if (auto* Primitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Primitive->SetSimulatePhysics(false);
	}

	AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

}

void AWeaponBase::DetachFromCharacter()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

}

void AWeaponBase::DropAtLocation(const FVector& Location, const FRotator& Rotation)
{
	DetachFromCharacter();

	SetActorLocation(Location);
	SetActorRotation(Rotation);

	if (auto* Primitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Primitive->SetSimulatePhysics(true);
		// 여기에서 콜라이더 모드도 설정하도록 하자.
	}

}

void AWeaponBase::StartAttackCollision()
{
	AlreadyHitActors.Empty();

	CapsuleComponent->SetCollisionProfileName(TEXT("Wpn_Collision_HitCheck"));

	const float ActiveTime = 0.5f; // 나중에 Data에서 가져올 수 있도록 코드를 수정하자.
	GetWorldTimerManager().SetTimer(CollisionTimerHandle, this, &AWeaponBase::StopAttackCollision, ActiveTime, false);

}

void AWeaponBase::StopAttackCollision()
{
	// Debugging: Log the actors that were hit during the attack
	UE_LOG(LogTemp, Warning, TEXT("=== Hit Actors List ==="));
	for (AActor* HitActor : AlreadyHitActors)
	{
		if (IsValid(HitActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("======================="));

	AlreadyHitActors.Empty();
	// 
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->OnComponentBeginOverlap.RemoveAll(this);
	GetWorldTimerManager().ClearTimer(CollisionTimerHandle);
	AlreadyHitActors.Empty();

}

void AWeaponBase::InteractInput(AActor* Interactor)
{
	if (Interactor == nullptr)
	{
		return;
	}

	if (ACharacter* Character = Cast<ACharacter>(Interactor))
	{
		if (UWeaponComponent* WeaponComponent = Character->FindComponentByClass<UWeaponComponent>())
		{
			WeaponComponent->EquipWeapon(this, TEXT("RightHandSocket"));
		}
	}

}

void AWeaponBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (UInteractionComponent* Interaction = OtherActor->FindComponentByClass<UInteractionComponent>())
	{
		Interaction->SetCurrentInteractable(this);
	}

}

void AWeaponBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (UInteractionComponent* Interaction = OtherActor->FindComponentByClass<UInteractionComponent>())
	{
		Interaction->ClearCurrentInteractable();
	}

}

FText AWeaponBase::GetInteractionText() const
{
	return FText();

}

void AWeaponBase::OnAttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner() && !AlreadyHitActors.Contains(OtherActor))
	{
		if (OtherActor->Implements<UIAttack>())
		{
			IIAttack::Execute_AttackHitCheck(OtherActor);
			AlreadyHitActors.Add(OtherActor);
		}
	}

}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IInteractable.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Hand,
	OneHand,
	TwoHand

};

UCLASS()
class RUNLAUNCHRUN_API AWeaponBase : public AActor, public IIInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void AttachToCharacter(class ACharacter* Character, FName SocketName);
	void DetachFromCharacter();
	void DropAtLocation(const FVector& Location, const FRotator& Rotation);

	void StartAttackCollision();
	void StopAttackCollision();

	virtual EWeaponType GetWeaponType() const { return EWeaponType::None; }

protected:
	virtual void InteractInput(AActor* Interactor) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual FText GetInteractionText() const override;

protected:
	UFUNCTION()
	void OnAttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TSet<TObjectPtr<class AActor>> AlreadyHitActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<class UWeaponData> WeaponData;

	FTimerHandle CollisionTimerHandle;

};
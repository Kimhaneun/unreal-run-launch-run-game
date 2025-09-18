// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_AttackHitCheck.h"
#include "GameFramework/Character.h"
#include "Component/WeaponComponent.h"
#include "Weapon/WeaponBase.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (auto* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if (auto* WeaponComponent = Character->FindComponentByClass<UWeaponComponent>())
		{
			if (AWeaponBase* Weapon = WeaponComponent->GetEquippedWeapon())
			{
				Weapon->StartAttackCollision();
			}
		}
	}

}

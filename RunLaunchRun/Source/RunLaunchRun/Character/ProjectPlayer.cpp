// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectComboActionData.h"
#include "Component/InteractionComponent.h"
#include "Component/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "Data/Weapon/WeaponData.h"
#include "UI/PlayerHUDWidget.h"
#include "UI/Player/MessageWidget.h"

AProjectPlayer::AProjectPlayer()
{
	float CapsuleRadius = 22.0f;
	float CapsuleHalfHeight = 80.0f;
	GetCapsuleComponent()->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);



	FVector MeshRelativeLocation(0.0f, 0.0f, -80.0f);
	FRotator MeshRelativeRotation(0.0f, -90.0f, 0.0f);
	GetMesh()->SetRelativeLocationAndRotation(MeshRelativeLocation, MeshRelativeRotation);



	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshReference(TEXT("/Script/Engine.SkeletalMesh'/Game/Environment/Character/Michelle/character.character'"));
	if (MeshReference.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshReference.Object);
	}



	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	const float SpringArmLength = 400.0f;
	SpringArmComponent->TargetArmLength = SpringArmLength;

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bDoCollisionTest = true;

	SpringArmComponent->bEnableCameraLag = true;



	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraComponent->bUsePawnControlRotation = false;



	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));



	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FRotator RotationSpeed(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->RotationRate = RotationSpeed;



	const float MaxWalkSpeed = 750.0f;
	const float MaxAcceleration = 4096.0f;
	const float BrakingDecelerationWalking = 4096.0f;

	const float JumpZVelocity = 700.0f;
	const float GravityScale = 1.8f;
	const float AirControl = 0.8f;

	const float BrakingFrictionFactor = 2.0f;

	const float MaxWalkSpeedCrouched = 350.0f;



	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
	GetCharacterMovement()->BrakingDecelerationWalking = BrakingDecelerationWalking;

	GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	GetCharacterMovement()->GravityScale = GravityScale;
	GetCharacterMovement()->AirControl = AirControl;

	GetCharacterMovement()->BrakingFrictionFactor = BrakingFrictionFactor;

	GetCharacterMovement()->MaxWalkSpeedCrouched = MaxWalkSpeedCrouched;



	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;



	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceReference(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/Michelle/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceReference.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceReference.Class);
	}



	// InputMappingContext
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextReference(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	if (InputMappingContextReference.Succeeded())
	{
		InputMappingContext = InputMappingContextReference.Object;
	}

	// InputAction
	static ConstructorHelpers::FObjectFinder<UInputAction> MovementActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Movement.IA_Movement'"));
	if (MovementActionReference.Succeeded())
	{
		MovementAction = MovementActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CameraRotationActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_CameraRotation.IA_CameraRotation'"));
	if (CameraRotationActionReference.Succeeded())
	{
		CameraRotationAction = CameraRotationActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Jump.IA_Jump'"));
	if (JumpActionReference.Succeeded())
	{
		JumpAction = JumpActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DashActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Dash.IA_Dash'"));
	if (DashActionReference.Succeeded())
	{
		DashAction = DashActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CrouchActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Crouch.IA_Crouch'"));
	if (CrouchActionReference.Succeeded())
	{
		CrouchAction = CrouchActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Attack.IA_Attack'"));
	if (AttackActionReference.Succeeded())
	{
		AttackAction = AttackActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SkillActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Skill.IA_Skill'"));
	if (SkillActionReference.Succeeded())
	{
		SkillAction = SkillActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> FocusTargetActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_FocusTarget.IA_FocusTarget'"));
	if (FocusTargetActionReference.Succeeded())
	{
		FocusTargetAction = FocusTargetActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Interact.IA_Interact'"));
	if (InteractActionReference.Succeeded())
	{
		InteractAction = InteractActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SwitchCameraDistanceActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_SwitchCameraDistance.IA_SwitchCameraDistance'"));
	if (SwitchCameraDistanceActionReference.Succeeded())
	{
		SwitchCameraDistanceAction = SwitchCameraDistanceActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> OpenSubMenuActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_OpenSubMenu.IA_OpenSubMenu'"));
	if (OpenSubMenuActionReference.Succeeded())
	{
		OpenSubMenuAction = OpenSubMenuActionReference.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CancelActionReference(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Cancel.IA_Cancel'"));
	if (CancelActionReference.Succeeded())
	{
		CancelAction = CancelActionReference.Object;
	}

	// AnimMontage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> OneHandAttackMontageReference(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Michelle/AM_One_Hand_Attack.AM_One_Hand_Attack'"));
	if (OneHandAttackMontageReference.Succeeded())
	{
		OneHandAttackMontage = OneHandAttackMontageReference.Object;
	}

	// ComboActionData
	static ConstructorHelpers::FObjectFinder<UProjectComboActionData> OneHandAttackDataReference(TEXT("/Script/RunLaunchRun.ProjectComboActionData'/Game/CharacterAction/DA_OneHandAttackData.DA_OneHandAttackData'"));
	if (OneHandAttackDataReference.Succeeded())
	{
		OneHandAttackData = OneHandAttackDataReference.Object;
	}

	static ConstructorHelpers::FClassFinder<UPlayerHUDWidget> PlayerHUDWidgetReference(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_PlayerHUD.WBP_PlayerHUD_C'"));
	if (PlayerHUDWidgetReference.Succeeded())
	{
		PlayerHUDWidgetClass = PlayerHUDWidgetReference.Class;
	}

}

void AProjectPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (EnhancedInputLocalPlayerSubsystem)
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
		}

		EnableInput(PlayerController);
	}

	PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(PlayerController, PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}

	if (PlayerHUDWidget && WeaponComponent && PlayerHUDWidget->WBP_NoWeaponMassage)
	{
		WeaponComponent->OnMessageFadeInDelegate.AddUObject(PlayerHUDWidget->WBP_NoWeaponMassage, &UMessageWidget::PlayFadeInAnimation);
		WeaponComponent->OnMessageFadeOutDelegate.AddUObject(PlayerHUDWidget->WBP_NoWeaponMassage, &UMessageWidget::PlayFadeOutAnimation);
	}

}

void AProjectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		LastGroundTime = GetWorld()->GetTimeSeconds();
	}

}

void AProjectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AProjectPlayer::InputMovement);
		EnhancedInputComponent->BindAction(CameraRotationAction, ETriggerEvent::Triggered, this, &AProjectPlayer::InputCameraRotation);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjectPlayer::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AProjectPlayer::StopJumping);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AProjectPlayer::InputCrouch);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProjectPlayer::InputAttack);


		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AProjectPlayer::InputInteract);
		EnhancedInputComponent->BindAction(SwitchCameraDistanceAction, ETriggerEvent::Started, this, &AProjectPlayer::InputSwitchCameraDistance);
		EnhancedInputComponent->BindAction(OpenSubMenuAction, ETriggerEvent::Started, this, &AProjectPlayer::InputSubMenuPressed);
		EnhancedInputComponent->BindAction(OpenSubMenuAction, ETriggerEvent::Completed, this, &AProjectPlayer::InputSubMenuReleased);
		EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Triggered, this, &AProjectPlayer::InputCancel);
	}

}

void AProjectPlayer::InputMovement(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputValue.X);
	AddMovementInput(RightDirection, InputValue.Y);

}

void AProjectPlayer::InputCameraRotation(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(-InputValue.Y);

}

void AProjectPlayer::InputDash(const FInputActionValue& Value)
{
}

void AProjectPlayer::InputCrouch(const FInputActionValue& Value)
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}

}

void AProjectPlayer::InputAttack(const FInputActionValue& Value)
{
	if (WeaponComponent && WeaponComponent->GetEquippedWeapon())
	{
		switch (WeaponComponent->GetEquippedWeapon()->GetWeaponType())
		{
		case EWeaponType::OneHand:
			ProcessOneHandAttack();
			break;
		case EWeaponType::TwoHand:
			break;
		default:
			break;
		}
	}

	if (WeaponComponent && WeaponComponent->GetEquippedWeapon() == nullptr)
	{
		float DelayTime = 1.0f;
		WeaponComponent->OnMessageFadeInDelegate.Broadcast();
		ExecuteAfterDelay(DelayTime, [this]()
			{
				WeaponComponent->OnMessageFadeOutDelegate.Broadcast();
			}, DelayHandle);
	}

}

void AProjectPlayer::InputSkill(const FInputActionValue& Value)
{
}

void AProjectPlayer::InputFocusTarget(const FInputActionValue& Value)
{
}

void AProjectPlayer::InputInteract(const FInputActionValue& Value)
{
	if (InteractionComponent)
	{
		InteractionComponent->TryInteract();
	}
}

void AProjectPlayer::InputSwitchCameraDistance(const FInputActionValue& Value)
{
}

void AProjectPlayer::InputSubMenuPressed(const FInputActionValue& Value)
{
	if (CurrentSubMenuState == ESubMenuState::Closed)
	{
		CurrentSubMenuState = ESubMenuState::QuickSelect;
		ShowSubMenuUI(CurrentSubMenuState);
	}

}

void AProjectPlayer::InputSubMenuReleased(const FInputActionValue& Value)
{
	if (CurrentSubMenuState == ESubMenuState::QuickSelect)
	{
		CurrentSubMenuState = ESubMenuState::Closed;
		HideSubMenuUI();
	}

}

void AProjectPlayer::InputCancel(const FInputActionValue& Value)
{
	if (CurrentSubMenuState == ESubMenuState::Inventory || CurrentSubMenuState == ESubMenuState::Map)
	{
		CurrentSubMenuState = ESubMenuState::Closed;
		HideSubMenuUI();
	}

}

void AProjectPlayer::ProcessOneHandAttack()
{
	if (CurrentComboCount == 0)
	{
		OneHandAttackBegin();
		return;
	}

	if (ComboTimerHandle.IsValid())
	{
		bHasNextComboCommand = true;
	}
	else
	{
		bHasNextComboCommand = false;
	}

}

void AProjectPlayer::OneHandAttackBegin()
{
	if (!GetCharacterMovement()->IsMovingOnGround())
	{
		return;
	}

	bWasOnGroundAtAttackStart = GetCharacterMovement()->IsMovingOnGround();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	CurrentComboCount = 1;

	// const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(OneHandAttackMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AProjectPlayer::OneHandAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, OneHandAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();

}

void AProjectPlayer::OneHandAttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	CurrentComboCount = 0;

}

void AProjectPlayer::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentComboCount - 1;

	// const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;
	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (OneHandAttackData->EffectiveFrameCount[ComboIndex] / OneHandAttackData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorldTimerManager().SetTimer(ComboTimerHandle, this, &AProjectPlayer::ComboActionCheck, ComboEffectiveTime, false);
	}
}

void AProjectPlayer::ComboActionCheck()
{
	ComboTimerHandle.Invalidate();

	if (bHasNextComboCommand && IsConsideredOnGround())
	{
		CurrentComboCount = FMath::Clamp(CurrentComboCount + 1, 1, OneHandAttackData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *OneHandAttackData->MontageSectionNamePrefix, CurrentComboCount);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_JumpToSection(NextSection, OneHandAttackMontage);

		SetComboCheckTimer();
		bHasNextComboCommand = false;
	}
}

void AProjectPlayer::ShowSubMenuUI(ESubMenuState NewState)
{
	// 여기서 델리게이트 사용하면 될려나?

}

void AProjectPlayer::HideSubMenuUI()
{
	// 여기도 

}

bool AProjectPlayer::IsConsideredOnGround() const
{
	if (!bWasOnGroundAtAttackStart)
	{
		return false;
	}

	const bool bRecentlyOnGround = (GetWorld()->GetTimeSeconds() - LastGroundTime) < GroundBufferTime;
	return bWasOnGroundAtAttackStart || bRecentlyOnGround;

}

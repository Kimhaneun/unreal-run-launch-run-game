// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ProjectCharacterBase.h"
#include "ProjectPlayer.generated.h"

/**
 *
 */

struct FInputActionValue;

UENUM(BlueprintType)
enum class ESubMenuState : uint8
{
	Closed,
	QuickSelect,
	Inventory,
	Map

};

UCLASS()
class RUNLAUNCHRUN_API AProjectPlayer : public AProjectCharacterBase
{
	GENERATED_BODY()

public:
	AProjectPlayer();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void InputMovement(const FInputActionValue& Value);
	void InputCameraRotation(const FInputActionValue& Value);
	void InputDash(const FInputActionValue& Value);
	void InputCrouch(const FInputActionValue& Value);
	void InputAttack(const FInputActionValue& Value);
	void InputSkill(const FInputActionValue& Value);
	void InputFocusTarget(const FInputActionValue& Value);
	void InputInteract(const FInputActionValue& Value);
	void InputSwitchCameraDistance(const FInputActionValue& Value);
	void InputSubMenuPressed(const FInputActionValue& Value);
	void InputSubMenuReleased(const FInputActionValue& Value);
	void InputCancel(const FInputActionValue& Value);

private:
	virtual void ProcessOneHandAttack();
	virtual void OneHandAttackBegin();
	virtual void OneHandAttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	void SetComboCheckTimer();
	void ComboActionCheck();

private:
	ESubMenuState CurrentSubMenuState;

	void ShowSubMenuUI(ESubMenuState NewState);
	void HideSubMenuUI();

private:
	UPROPERTY()
	AActor* CurrentInteractableTarget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputMappingContext")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> CameraRotationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> SkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> FocusTargetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> SwitchCameraDistanceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> OpenSubMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<class UInputAction> CancelAction;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<class UInteractionComponent> InteractionComponent;

protected:
	bool IsConsideredOnGround() const;

	bool bWasOnGroundAtAttackStart = false;
	float LastGroundTime = 0.0f;
	const float GroundBufferTime = 0.3f;

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<class UAnimMontage> OneHandAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<class UProjectComboActionData> OneHandAttackData;

	int32 CurrentComboCount = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UPlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<class  UPlayerHUDWidget> PlayerHUDWidget;

	FTimerHandle DelayHandle;

};

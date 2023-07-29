// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputMappingContext.h"
#include "JamPlayerCharacter.generated.h"

UENUM()
enum ECameraType
{
	ECT_FirstPerson = 0 UMETA(DisplayName = "First Person"),
	ECT_ThirdPerson = 1 UMETA(DisplayName = "Third Person")
};

class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract)
class ICOJAM_API AJamPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AJamPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	
	/** Spring Arm */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Should the player be in TPS or FPS */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Camera", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECameraType> PlayerCameraType = ECT_FirstPerson;

	/** Allow the player to switch between TPS and FPS */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Camera", meta = (AllowPrivateAccess = "true"))
	bool bAllowCameraSwitch = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Camera", meta = (AllowPrivateAccess = "true"))
	float TPSArmLength = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Camera", meta = (AllowPrivateAccess = "true"))
	FVector FPSArmOffset = FVector(20.f, 0.f, 70.f);
	
	/** Invert Y Axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Input", meta = (AllowPrivateAccess = "true"))
	bool bInvertYAxis = true;

	/** Walk Speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 500.f;

	/** Sprint Speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 650.f;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Move(const float ValueX, const float ValueY);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Look(const float ValueX, const float ValueY);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void ThrowDistraction();
	
	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Sprint() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void StopSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void SwitchCamera();

	void SetCameraType(const ECameraType NewCameraType);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "JamPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ICOJAM_API AJamPlayerCharacter : public ACharacter
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

	/** Invert Y Axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Input", meta = (AllowPrivateAccess = "true"))
	bool bInvertYAxis = true;

	/** INPUT */
	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Move(const float ValueX, const float ValueY);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Look(const float ValueX, const float ValueY);
	

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void OnCrouchActionStarted(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void OnCrouchActionEnded(const FInputActionValue& Value);

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void OnSprintActionStarted(const FInputActionValue& Value);

	void OnSprintActionEnded(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

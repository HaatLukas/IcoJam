// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "JamPlayerCharacter.generated.h"

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

	/** Invert Y Axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Input", meta = (AllowPrivateAccess = "true"))
	bool bInvertYAxis = true;

	/** Sprint Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Input", meta = (AllowPrivateAccess = "true"))
	float SprintMultiplier = 1.25f;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Move(const float ValueX, const float ValueY);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Look(const float ValueX, const float ValueY);

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void ThrowDistraction();
	
	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	void Sprint() const;

	void StopSprinting() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/JamPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Debug.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AJamPlayerCharacter::AJamPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	SpringArm->TargetArmLength= 400.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

}

void AJamPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJamPlayerCharacter::Move(const float ValueX, const float ValueY)
{

	if (Controller != nullptr)
	{
		// get forward vector
		const FVector ForwardDirection = GetActorForwardVector();
	
		// get right vector 
		const FVector RightDirection = GetActorRightVector();

		// add movement 
		AddMovementInput(ForwardDirection, ValueY);
		AddMovementInput(RightDirection, ValueX);
	}
	else
	{
		Print(this,"No Controller");
	}
}

void AJamPlayerCharacter::Look(const float ValueX, const float ValueY)
{
	const int InvertFactor = bInvertYAxis ? -1 : 1;

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(ValueX);
		AddControllerPitchInput(ValueY * InvertFactor);
	}
}

void AJamPlayerCharacter::OnCrouchActionStarted(const FInputActionValue& Value)
{
}

void AJamPlayerCharacter::OnCrouchActionEnded(const FInputActionValue& Value)
{
}

void AJamPlayerCharacter::ThrowDistraction(const FInputActionValue& Value)
{
	if (Value.Get<bool>() == true)
	{
		Print(this, FString::Printf(TEXT("Throw a object")));
	}
}

void AJamPlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void AJamPlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void AJamPlayerCharacter::OnSprintActionStarted(const FInputActionValue& Value)
{
}

void AJamPlayerCharacter::OnSprintActionEnded(const FInputActionValue& Value)
{
}

// Called every frame
void AJamPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJamPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &AJamPlayerCharacter::ThrowDistraction);

	}

}


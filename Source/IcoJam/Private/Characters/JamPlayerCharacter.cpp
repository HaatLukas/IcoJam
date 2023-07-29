// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/JamPlayerCharacter.h"
#include "Debug.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

void AJamPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCameraType(PlayerCameraType);
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

void AJamPlayerCharacter::Sprint() const
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AJamPlayerCharacter::StopSprinting() const
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AJamPlayerCharacter::SwitchCamera()
{
	if (!bAllowCameraSwitch) return;

	if (PlayerCameraType == ECT_FirstPerson)
	{
		SetCameraType(ECT_ThirdPerson);
	}
	else
	{
		SetCameraType(ECT_FirstPerson);
	}
}

void AJamPlayerCharacter::SetCameraType(const ECameraType NewCameraType)
{
	switch (NewCameraType)
	{
	case ECT_FirstPerson:
		{
			SpringArm->TargetArmLength = 0.f;
			SpringArm->SetRelativeLocation(FPSArmOffset);
			GetMesh()->SetOwnerNoSee(true);
			PlayerCameraType = ECT_FirstPerson;
			
			break;
		}

	case ECT_ThirdPerson:
		{
			SpringArm->TargetArmLength = TPSArmLength;
			SpringArm->SetRelativeLocation(FVector::ZeroVector);
			GetMesh()->SetOwnerNoSee(false);
			PlayerCameraType = ECT_ThirdPerson;
			
			break;
		}
	}
}

void AJamPlayerCharacter::HeadBobbing()
{
	const auto PC = Cast<APlayerController>(GetController());

	if (!PC) return;

	const auto Speed = GetVelocity().Size();

	if (Speed > 0.f && Speed <= WalkSpeed)
	{
		PC->PlayerCameraManager->StartCameraShake(WalkingHeadbobClass);
	}
	else if (Speed > WalkSpeed && Speed <= SprintSpeed)
	{
		PC->PlayerCameraManager->StartCameraShake(SprintingHeadbobClass);
	}
	else
	{
		PC->PlayerCameraManager->StartCameraShake(IdleHeadbobClass);
	}
}

void AJamPlayerCharacter::ThrowDistraction()
{
	Print(this, "Throw a object");
}

void AJamPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJamPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


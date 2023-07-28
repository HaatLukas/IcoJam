// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseEnemy.generated.h"

class UPawnSensingComponent;

UCLASS()
class ICOJAM_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(VisibleAnywhere)
		UPawnSensingComponent* SensingComponent;

//	UFUNCTION()
	//	void PawnSeen(APawn* SeenPawn);
	

};


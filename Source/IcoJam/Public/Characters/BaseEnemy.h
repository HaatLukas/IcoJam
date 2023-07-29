// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseEnemy.generated.h"

class UPawnSensingComponent;
class AActor;

UCLASS(Abstract)
class ICOJAM_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float ChasingSpeed = 500.f;

	UPROPERTY( EditAnywhere, Category = "Movement")
		float PatrolSpeed = 350.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float WaitMin = 3.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float WaitMax = 5.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		double PatrolRadius = 4000.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		double ChaseRadius = 1000.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		AActor* CurrentPatrolTarget;
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		TArray<AActor*>PatrolTargets;

	UPROPERTY(BlueprintReadOnly,Category = "AI")
		class AAIController* EnemyController;
	
	//UPROPERTY()
	AActor* ChooseRandomTarget();
	
private:
	void InitializeEnemy();
	
	/*
	 Navivgation
	*/

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* SensingComponent;
	void PatrolTimerFinished() const;
	bool InTargetRange(AActor* Target, double AcceptanceRadius) const;

	/*
	* AI Stuff
	*/

	UFUNCTION(BlueprintCallable, Category = "AI")
		void OnPawnSeen(APawn* SeenPawn);

	//UPROPERTY()
	//bool GenerateRandomLocation();
	
	void MoveToTarget(const AActor* Target) const;
	void PatrolToTarget();
	
	FTimerHandle PatrolTimer;
};


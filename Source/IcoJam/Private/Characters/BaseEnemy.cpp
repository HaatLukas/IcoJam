// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BaseEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Debug.h"
#include "Perception/PawnSensingComponent.h"
#include "Navigation/PathFollowingComponent.h"


ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));
	SensingComponent->SightRadius = 4000.f;
	SensingComponent->SetPeripheralVisionAngle(45.f);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeEnemy();
}

void ABaseEnemy::InitializeEnemy()
{
	if (SensingComponent)
	{
		SensingComponent->OnSeePawn.AddDynamic(this, &ABaseEnemy::OnPawnSeen);
		PrintLog("SensingComponentActive");
		Tags.Add(FName("Enemy"));
	}
	EnemyController = Cast<AAIController>(GetController());
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	SpawnDefaultController();
}

void ABaseEnemy::PatrolTimerFinished() const
{
	MoveToTarget(CurrentPatrolTarget);
}

bool ABaseEnemy::InTargetRange(AActor* Target, double AcceptanceRadius) const
{	
	{
		if (Target == nullptr) return false;
		const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
		return DistanceToTarget <= AcceptanceRadius;
	}
}

void ABaseEnemy::OnPawnSeen(APawn* SeenPawn)
{
	//Print(this,  FString::Printf(TEXT("I see: %s"), *SeenPawn->GetName()));
	MoveToTarget(SeenPawn);
}

/*
bool ABaseEnemy::GenerateRandomLocation()
{
	return false;
}*/

AActor* ABaseEnemy::ChooseRandomTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != CurrentPatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}
	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0)
	{
		const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
		return ValidTargets[TargetSelection];
	}
	return nullptr;
}

void ABaseEnemy::MoveToTarget(const AActor* Target) const
{
	if (EnemyController == nullptr || Target == nullptr) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(35.f);
	EnemyController->MoveTo(MoveRequest);
}

void ABaseEnemy::PatrolToTarget()
{
	if (InTargetRange(CurrentPatrolTarget, PatrolRadius))
	{
		CurrentPatrolTarget = ChooseRandomTarget();
		const float WaitTime = FMath::FRandRange(WaitMin, WaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &ABaseEnemy::PatrolTimerFinished, WaitTime);
	}
}


void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PatrolToTarget();
}
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


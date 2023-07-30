#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomGenerator.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ARoomGenerator : public AActor
{
	GENERATED_BODY()

public:
	ARoomGenerator();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GenerateRoom();

protected:
	UFUNCTION()
	void GenerateWalls();

	void GenerateComplexities();

	UFUNCTION()
	void GenerateInternalWalls();

	UFUNCTION()
	void GeneratePillars();

	UFUNCTION()
	void GenerateFloor();

	UFUNCTION()
	void GenerateCeiling();
	
	UFUNCTION()
	UStaticMeshComponent* SpawnComponent(FVector Transform, FRotator Rotation, UStaticMesh* Mesh, FString NamePrefix, int x, int y);

	UFUNCTION()
	void SpawnWallOrDoor(const FVector& RelativeTransform_Location, const FRotator& RelativeTransform_Rotator);

	UFUNCTION()
	void SpawnWallLight(const FVector& RelativeTransform_Location, const FRotator& RelativeTransform_Rotator);
	
	UFUNCTION()
	void IncrementIndex();
	
	UFUNCTION()
	void ResetIndex();

	UFUNCTION()
	void DeleteOldObjects() const;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config", meta=(AllowPrivateAccess=true))
	FVector RoomSize = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Room|Config")
	int32 CurrentIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Floor", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> FloorMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Floor", meta=(AllowPrivateAccess=true))
	FVector FloorSize = FVector(200.0f, 200.0f, 200.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Floor", meta=(AllowPrivateAccess=true))
	FRotator FloorRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> WallMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall", meta=(AllowPrivateAccess=true))
	FVector WallSize = FVector(200.0f, 200.0f, 300.0f);;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall", meta=(AllowPrivateAccess=true))
	FRotator WallRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Lights", meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> WallLightClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Lights", meta=(AllowPrivateAccess=true))
	int32 WallLightFrequency = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true))
	bool bGenerateComplexities = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="!bGeneratePillars bGenerateComplexities"))
	bool bGenerateInternalWalls = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGenerateInternalWalls"))
	TObjectPtr<UStaticMesh> InternalWallMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGenerateInternalWalls"))
	FVector InternalWallSize = FVector(200.0f, 200.0f, 300.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGenerateInternalWalls"))
	FVector InternalWallScale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGenerateInternalWalls"))
	float InternalWallPercentage = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="!bGenerateInternalWalls bGenerateComplexities"))
	bool bGeneratePillars = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGeneratePillars"))
	TObjectPtr<UStaticMesh> PillarMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGeneratePillars"))
	FVector PillarSize = FVector(200.0f, 200.0f, 300.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGeneratePillars"))
	FVector PillarScale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Wall|Complexities", meta=(AllowPrivateAccess=true, EditCondition="bGeneratePillars"))
	float PillarPercentage = 0.5f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Ceiling", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> CeilingMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Ceiling", meta=(AllowPrivateAccess=true))
	FRotator CeilingRotation = FRotator(0.0f, 0.0f, -90.0f);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Door", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> DoorMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Door", meta=(AllowPrivateAccess=true))
	int32 EntranceDoorIndex = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room|Config|Door", meta=(AllowPrivateAccess=true))
	int32 ExitDoorIndex = -1;
};
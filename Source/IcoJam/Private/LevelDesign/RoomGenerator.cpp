#include "LevelDesign/RoomGenerator.h"
#include "Debug.h"

ARoomGenerator::ARoomGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
}

void ARoomGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void ARoomGenerator::GenerateFloor()
{
	const int LastIndexX = RoomSize.X;
	const int LastIndexY = RoomSize.Y;

	for (int x = 0; x < LastIndexX; x++)
	{
		for (int y = 1; y < LastIndexY + 1; y++)
		{
			const FVector Transform = FVector(x * FloorSize.X, y * FloorSize.Y, 0.0f);

			UStaticMeshComponent* Floor = SpawnComponent(Transform, FloorRotation, FloorMesh, "FloorTile", x, y);
			Floor->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void ARoomGenerator::GenerateCeiling()
{
	const int LastIndexX = RoomSize.X;
	const int LastIndexY = RoomSize.Y;

	for (int x = 0; x < LastIndexX; x++)
	{
		for (int y = 1; y < LastIndexY + 1; y++)
		{
			const FVector Transform = FVector(x * FloorSize.X, y * FloorSize.Y, WallSize.Z);

			UStaticMeshComponent* Ceiling = SpawnComponent(Transform, CeilingRotation, CeilingMesh, "CeilingTile", x, y);
			Ceiling->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			
		}
	}
}

void ARoomGenerator::GenerateWalls()
{
	// Place walls along the X axis
	for (int x = 0; x < RoomSize.X; x++)
	{
		const FVector Transform = FVector(x * WallSize.X, 0.0f, 0.0f);
		SpawnWallOrDoor(Transform, FRotator::ZeroRotator);
	}

	// Continue placing walls along the Y axis
	for (int y = 0; y < RoomSize.Y; y++)
	{
		const FVector Transform = FVector(RoomSize.X * WallSize.X, y * WallSize.Y, 0.0f);
		SpawnWallOrDoor(Transform, FRotator(0.0f, 90.0f, 0.0f));
	}

	// Place walls on the opposite side of the X axis (we need to remove one WallSize.X length to accomodate rotation)
	for (int x = RoomSize.X; x > 0; x--)
	{
		const FVector Transform = FVector(x * WallSize.X - WallSize.X, RoomSize.Y * WallSize.Y, 0.0f);
		SpawnWallOrDoor(Transform, FRotator::ZeroRotator);
	}

	// Finish placing walls on the opposite Y axis (we need to remove one WallSize.Y length to accomodate rotation)
	for (int y = RoomSize.Y; y > 0; y--)
	{
		const FVector Transform = FVector(0.0f, y * WallSize.Y - WallSize.Y, 0.0f);
		SpawnWallOrDoor(Transform, FRotator(0.0f, 90.0f, 0.0f));
	}
}

void ARoomGenerator::GenerateComplexities()
{
	if (!bGenerateComplexities) return;

	if (bGenerateInternalWalls)
	{
		GenerateInternalWalls();
	}
	else if (bGeneratePillars)
	{
		GeneratePillars();
	}
	else
	{
		Print(this, "No complexities selected!");
	}
}

void ARoomGenerator::GenerateInternalWalls()
{
	if (!InternalWallMesh)
	{
		Print(this, "Missing InternalWallMesh!");
		return;
	}

	// Calculate the total number of possible positions for the walls
	const int TotalPositions = (RoomSize.X - 2) * (RoomSize.Y - 2); // -2 to exclude the perimeter of the room

	// Calculate the number of walls to place
	const int WallsToPlace = FMath::RoundToInt(TotalPositions * InternalWallPercentage);

	// Randomly place the walls
	for (int i = 0; i < WallsToPlace; i++)
	{
		const int X = FMath::RandRange(1.0, RoomSize.X - 2); // avoid placing walls on the edges
		const int Y = FMath::RandRange(1.0, RoomSize.Y - 2); // avoid placing walls on the edges

		const FVector Transform = FVector(X * InternalWallSize.X, Y * InternalWallSize.Y, 0.0f);

		// Randomly rotate some walls by 90 degrees
		const FRotator Rotation = FMath::RandBool() ? FRotator::ZeroRotator : FRotator(0.0f, 90.0f, 0.0f);

		UStaticMeshComponent* Wall = SpawnComponent(Transform, Rotation, InternalWallMesh, "InternalWall", X, Y);
		Wall->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ARoomGenerator::GeneratePillars()
{
	if (!PillarMesh)
	{
		Print(this, "Missing PillarMesh!");
		return;
	}

	// Calculate the total number of possible positions for the walls
	const int TotalPositions = (RoomSize.X - 2) * (RoomSize.Y - 2); // -2 to exclude the perimeter of the room

	// Calculate the number of walls to place
	const int PillarsToPlace = FMath::RoundToInt(TotalPositions * PillarPercentage);

	// Randomly place the walls
	for (int i = 0; i < PillarsToPlace; i++)
	{
		const int X = FMath::RandRange(1.0, RoomSize.X - 2); // avoid placing walls on the edges
		const int Y = FMath::RandRange(1.0, RoomSize.Y - 2); // avoid placing walls on the edges

		const FVector Transform = FVector(X * PillarSize.X, Y * PillarSize.Y, 0.0f);

		UStaticMeshComponent* Pillar = SpawnComponent(Transform, FRotator::ZeroRotator, PillarMesh, "Pillar", X, Y);
		Pillar->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.2f));
		Pillar->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

UStaticMeshComponent* ARoomGenerator::SpawnComponent(FVector Transform, FRotator Rotation, UStaticMesh* Mesh, FString NamePrefix, int x, int y)
{
	UStaticMeshComponent* NewComponent = NewObject<UStaticMeshComponent>(this, FName(*FString::Printf(TEXT("%s_%d_%d"), *NamePrefix, x, y)));
	NewComponent->SetStaticMesh(Mesh);
	NewComponent->SetRelativeLocation(Transform);
	NewComponent->SetRelativeRotation(Rotation);
	NewComponent->RegisterComponent();
	return NewComponent;
}

void ARoomGenerator::SpawnWallLight(const FVector& RelativeTransform_Location, const FRotator& RelativeTransform_Rotator)
{
	FRotator LightRotation = RelativeTransform_Rotator;

	// If the wall is on the opposite side or at origin, rotate the light 180 degrees
	if (RelativeTransform_Location.Y == RoomSize.Y * WallSize.Y || RelativeTransform_Location.X == 0)
	{
		LightRotation.Yaw += 180.0f;
	}
			
	UChildActorComponent* Light = NewObject<UChildActorComponent>(this, FName(*FString::Printf(TEXT("Light_%d"), CurrentIndex)));
	Light->SetChildActorClass(WallLightClass);
	Light->SetRelativeLocation(RelativeTransform_Location + FVector(0.0f, 0.0f, 250.0f));
	Light->SetRelativeRotation(LightRotation);
	Light->CreateChildActor();
	Light->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}


void ARoomGenerator::SpawnWallOrDoor(const FVector& RelativeTransform_Location, const FRotator& RelativeTransform_Rotator)
{
	IncrementIndex();

	if (CurrentIndex == EntranceDoorIndex ||  CurrentIndex == ExitDoorIndex)
	{
		UStaticMeshComponent* Door = SpawnComponent(RelativeTransform_Location, RelativeTransform_Rotator, DoorMesh, "Door", CurrentIndex, 0);
		Door->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		UStaticMeshComponent* Wall = SpawnComponent(RelativeTransform_Location, RelativeTransform_Rotator, WallMesh, "Wall", CurrentIndex, 0);
		Wall->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		if (WallLightClass && CurrentIndex % WallLightFrequency == 0)
		{
			SpawnWallLight(RelativeTransform_Location, RelativeTransform_Rotator);
		}
	}
}


void ARoomGenerator::IncrementIndex()
{
	CurrentIndex++;
}

void ARoomGenerator::ResetIndex()
{
	CurrentIndex = 0;
}

void ARoomGenerator::DeleteOldObjects() const
{
	TArray<UActorComponent*> Components;
	GetComponents(UActorComponent::StaticClass(), Components);
	
	TArray<UActorComponent*> ChildActorComponents;
	GetComponents(UChildActorComponent::StaticClass(), ChildActorComponents);
	
	for (UActorComponent* Component : Components)
	{
		if (Component == GetRootComponent()) continue;
		
		Component->DestroyComponent();
	}

	for (UActorComponent* Component : ChildActorComponents)
	{
		
		if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(Component))
		{
			ChildActorComponent->DestroyChildActor();
			ChildActorComponent->DestroyComponent();
		}
	}
}



void ARoomGenerator::GenerateRoom()
{
	if (!FloorMesh || !WallMesh || !DoorMesh)
	{
		Print(this, "Missing mesh(es)!");
		return;
	}

	DeleteOldObjects();
	
	ResetIndex();
	GenerateFloor();
	GenerateCeiling();
	GenerateWalls();
	GenerateComplexities();
}

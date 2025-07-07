#include "Spawner/BoxRandomSpawner.h"
#include "Components/BoxComponent.h"

ABoxRandomSpawner::ABoxRandomSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(SceneRoot);
}

void ABoxRandomSpawner::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
	Setup();
}

void ABoxRandomSpawner::Spawn()
{
	if (SpawnActorClass)
	{
		if (UWorld* World = GetWorld())
		{
			for (int n = 0; n < SpawnCount; n++)
			{
				FVector SpawnLocation = GetRandomPositionInVolume();
				FRotator SpawnRotation = GetActorRotation();
				FActorSpawnParameters SpawnParam;
				AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnActorClass, SpawnLocation, SpawnRotation, SpawnParam);
				SpawnedActors.Add(SpawnedActor);
			}
		}
	}
}

void ABoxRandomSpawner::Setup()
{
}

FVector ABoxRandomSpawner::GetRandomPositionInVolume() const
{
	FVector BoxExtend = SpawnVolume->GetScaledBoxExtent();
	FVector BoxOrigin = SpawnVolume->GetComponentLocation();
	FVector RandomVector(
		FMath::FRandRange(-BoxExtend.X, BoxExtend.X),
		FMath::FRandRange(-BoxExtend.Y, BoxExtend.Y),
		FMath::FRandRange(-BoxExtend.Z, BoxExtend.Z));
	return BoxOrigin + RandomVector;
}

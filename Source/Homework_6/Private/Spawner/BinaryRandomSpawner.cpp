#include "Spawner/BinaryRandomSpawner.h"
#include "Components/ArrowComponent.h"

ABinaryRandomSpawner::ABinaryRandomSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpawnDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnDirection"));
	SpawnDirection->SetupAttachment(SceneRoot);

	SpawnCount = 5;
	SpawnIntervalX = 200.0f;
	SpawnIntervalY = 200.0f;
}

void ABinaryRandomSpawner::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
	Setup();
}

/// <summary>
/// ������ ������ ����, 2���� ��ֹ��� N�� �����ϴ� �Լ�
/// </summary>
void ABinaryRandomSpawner::Spawn()
{
	if (SpawnActorClass == nullptr)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		FVector RootLocation = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		FVector RightVector = GetActorRightVector();
		for (int n = 0; n < SpawnCount; n++)
		{
			float DeltaX = SpawnIntervalX * n;
			float DeltaY = SpawnIntervalY / 2.0f;
			FVector SpawnLeftLocation = RootLocation + ForwardVector * DeltaX - RightVector * DeltaY;
			FVector SpawnRightLocation = RootLocation + ForwardVector * DeltaX + RightVector * DeltaY;
			FRotator SpawnRotation = GetActorRotation();
			FActorSpawnParameters SpawnParam;
			AActor* SpawnedLeftActor = World->SpawnActor<AActor>(SpawnActorClass, SpawnLeftLocation, SpawnRotation, SpawnParam);
			AActor* SpawnedRightActor = World->SpawnActor<AActor>(SpawnActorClass, SpawnRightLocation, SpawnRotation, SpawnParam);
		
			SpawnedLeftActors.Add(SpawnedLeftActor);
			SpawnedRightActors.Add(SpawnedRightActor);
		}
	}
}

/// <summary>
/// ���� ��, ������ ��ֹ��� �Ӽ��� �����ϴ� �Լ�
/// </summary>
void ABinaryRandomSpawner::Setup()
{
}

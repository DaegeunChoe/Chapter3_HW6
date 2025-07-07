#include "Spawner/GearRandomSpawner.h"
#include "Obstacle/RotateObstacle.h"

AGearRandomSpawner::AGearRandomSpawner()
{
	MinSpeed = 10.0f;
	MaxSpeed = 90.0f;
}

void AGearRandomSpawner::Setup()
{
	float Delta = 30.0f;
	for (int n = 0; n < SpawnCount; n++)
	{
		ARotateObstacle* Gear = nullptr;
		int32 dice = FMath::RandRange(0, 1);
		if (SpawnedActors.IsValidIndex(n))
		{
			Gear = Cast<ARotateObstacle>(SpawnedActors[n]);
		}
		if (Gear)
		{
			Gear->AngleSpeed = FMath::RandRange(MinSpeed / Delta, MaxSpeed / Delta) * Delta;
			if (dice == 1)
			{
				Gear->RotateTo *= -1;
			}
			Gear->InitMovement();
		}
	}
}

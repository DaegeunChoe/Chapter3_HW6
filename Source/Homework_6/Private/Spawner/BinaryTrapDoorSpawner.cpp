#include "Spawner/BinaryTrapDoorSpawner.h"
#include "Obstacle/TrapDoor.h"

ABinaryTrapDoorSpawner::ABinaryTrapDoorSpawner()
{
	TrapDelay = 0.1f;
	AngleSpeed = 360.0f;
	AngleOpen = 90.0f;
}

void ABinaryTrapDoorSpawner::Setup()
{
	for (int n = 0; n < SpawnCount; n++)
	{
		ATrapDoor* ToOpen = nullptr;
		ATrapDoor* ToClose = nullptr;
		int32 dice = FMath::RandRange(0, 1);
		if (dice == 1)
		{
			if (SpawnedLeftActors.IsValidIndex(n))
			{
				ToOpen = Cast<ATrapDoor>(SpawnedLeftActors[n]);
			}
			if (SpawnedRightActors.IsValidIndex(n))
			{
				ToClose = Cast<ATrapDoor>(SpawnedRightActors[n]);
			}
		}
		else
		{
			if (SpawnedLeftActors.IsValidIndex(n))
			{
				ToClose = Cast<ATrapDoor>(SpawnedLeftActors[n]);
			}
			if (SpawnedRightActors.IsValidIndex(n))
			{
				ToOpen = Cast<ATrapDoor>(SpawnedRightActors[n]);
			}
		}
		if (ToOpen)
		{
			ToOpen->TrapDelay = TrapDelay;
			ToOpen->AngleSpeed = AngleSpeed;
			ToOpen->AngleOpen = AngleOpen;
		}
		if (ToClose)
		{
			ToClose->TrapDelay = -1;
			ToClose->AngleSpeed = -1;
			ToClose->AngleOpen = -1;
		}
	}
}

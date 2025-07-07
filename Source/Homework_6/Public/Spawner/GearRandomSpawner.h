#pragma once

#include "CoreMinimal.h"
#include "Spawner/BoxRandomSpawner.h"
#include "GearRandomSpawner.generated.h"

UCLASS()
class HOMEWORK_6_API AGearRandomSpawner : public ABoxRandomSpawner
{
	GENERATED_BODY()

public:
	AGearRandomSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MinSpeed;

protected:
	virtual void Setup() override;
};

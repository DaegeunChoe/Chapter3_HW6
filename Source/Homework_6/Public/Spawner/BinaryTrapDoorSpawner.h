#pragma once

#include "CoreMinimal.h"
#include "Spawner/BinaryRandomSpawner.h"
#include "BinaryTrapDoorSpawner.generated.h"


UCLASS()
class HOMEWORK_6_API ABinaryTrapDoorSpawner : public ABinaryRandomSpawner
{
	GENERATED_BODY()

public:
	ABinaryTrapDoorSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float TrapDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float AngleSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float AngleOpen;
	
protected:
	virtual void Setup() override;
};

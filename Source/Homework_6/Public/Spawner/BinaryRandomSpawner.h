#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BinaryRandomSpawner.generated.h"

class UArrowComponent;

UCLASS()
class HOMEWORK_6_API ABinaryRandomSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABinaryRandomSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	int32 SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float SpawnIntervalX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float SpawnIntervalY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	TSubclassOf<AActor> SpawnActorClass;


protected:
	virtual void BeginPlay() override;
	virtual void Spawn();
	virtual void Setup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Components")
	TObjectPtr<UArrowComponent> SpawnDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Actors")
	TArray<AActor*> SpawnedLeftActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Actors")
	TArray<AActor*> SpawnedRightActors;
};

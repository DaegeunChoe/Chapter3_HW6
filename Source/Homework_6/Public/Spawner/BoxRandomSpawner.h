#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxRandomSpawner.generated.h"

class UBoxComponent;

UCLASS()
class HOMEWORK_6_API ABoxRandomSpawner : public AActor
{
	GENERATED_BODY()

public:
	ABoxRandomSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	int32 SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	TSubclassOf<AActor> SpawnActorClass;


protected:
	virtual void BeginPlay() override;
	virtual void Spawn();
	virtual void Setup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Component")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Component")
	TObjectPtr<UBoxComponent> SpawnVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Actors")
	TArray<AActor*> SpawnedActors;

private:
	FVector GetRandomPositionInVolume() const;
};

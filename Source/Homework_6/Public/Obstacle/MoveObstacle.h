#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle/ObstacleBase.h"
#include "Animation/TAnimationHelper.h"
#include "MoveObstacle.generated.h"

class UArrowComponent;

UCLASS()
class HOMEWORK_6_API AMoveObstacle : public AActor, public IObstacleBase
{
	GENERATED_BODY()
	
public:	
	AMoveObstacle();

	virtual void Tick(float DeltaTime) override;
	virtual void InitMovement() override;
	virtual void Movement(float DeltaTime) override;
	virtual FName GetTypeName() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Component")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Movement")
	TObjectPtr<UArrowComponent> ForwardArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	FVector MoveTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	EAnimationTravelType TravelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	EAnimationTransitionType TransitionType;

protected:
	virtual void BeginPlay() override;

private:
	TAnimationHelper<FVector> AnimationHelper;
};

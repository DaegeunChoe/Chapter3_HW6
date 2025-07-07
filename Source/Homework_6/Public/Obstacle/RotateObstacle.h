#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle/ObstacleBase.h"
#include "Animation/TAnimationHelper.h"
#include "RotateObstacle.generated.h"

class UArrowComponent;

UCLASS()
class HOMEWORK_6_API ARotateObstacle : public AActor, public IObstacleBase
{
	GENERATED_BODY()
	
public:	
	ARotateObstacle();

	virtual void Tick(float DeltaTime) override;
	virtual void InitMovement() override;
	virtual void Movement(float DeltaTime) override;
	virtual FName GetTypeName() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Component")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle|Component")
	TObjectPtr<UArrowComponent> YawAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	FRotator RotateTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	float AngleSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	EAnimationTransitionType TransitionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle|Movement")
	EAnimationTravelType TravelType;

protected:
	virtual void BeginPlay() override;

private:
	TAnimationHelper<FRotator> AnimationHelper;
};

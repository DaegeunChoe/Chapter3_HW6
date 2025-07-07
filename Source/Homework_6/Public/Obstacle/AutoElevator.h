#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/TAnimationHelper.h"
#include "AutoElevator.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class HOMEWORK_6_API AAutoElevator : public AActor
{
	GENERATED_BODY()
	
public:
	AAutoElevator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Component")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Component")
	TObjectPtr<UArrowComponent> UpDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Component")
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement")
	float MoveDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement")
	float WaitDuration;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnter(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnExit(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle WaitTimer;

	FTimerHandle MoveAnimationTimer;

private:
	void UpdateMoveAnimation();
	void OnEndWait();

	TAnimationHelper<FVector> AnimationHelper;

	FVector Source;
	FVector Destination;
	float AnimationInterval;
	float AnimationTime;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/TAnimationHelper.h"
#include "TrapDoor.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class HOMEWORK_6_API ATrapDoor : public AActor
{
	GENERATED_BODY()
	
public:
	ATrapDoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<USceneComponent> DoorLeftAxis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<USceneComponent> DoorRightAxis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<UStaticMeshComponent> DoorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<UStaticMeshComponent> DoorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<UArrowComponent> DropDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trapdoor|Component")
	TObjectPtr<UBoxComponent> TrapTrigerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trapdoor|Movement")
	float TrapDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trapdoor|Movement")
	float AngleSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trapdoor|Movement")
	float AngleOpen;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle TrapTimer;

	FTimerHandle OpenAnimationTimer;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void OnActivate();
	void OpenAnimationUpdate();

	TAnimationHelper<FRotator> OpenLeftHelper;
	TAnimationHelper<FRotator> OpenRightHelper;

	bool bIsActivated;
	float AnimationInterval;
	float AnimationTime;
};

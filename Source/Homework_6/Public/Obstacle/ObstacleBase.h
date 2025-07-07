#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObstacleBase.generated.h"

UINTERFACE(MinimalAPI)
class UObstacleBase : public UInterface
{
	GENERATED_BODY()
};

class HOMEWORK_6_API IObstacleBase
{
	GENERATED_BODY()

public:
	// 이 방해물이 움직이기 위한 조건을 만족했는가?
	virtual bool ShouldMove();

	// 이동 관련 값 초기화
	virtual void InitMovement() = 0;

	// 이 방해물이 움직이는 방법을 정의
	virtual void Movement(float DeltaTime) = 0;

	// 방해물 타입
	virtual FName GetTypeName() const = 0;
};

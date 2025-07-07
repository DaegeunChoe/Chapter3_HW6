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
	// �� ���ع��� �����̱� ���� ������ �����ߴ°�?
	virtual bool ShouldMove();

	// �̵� ���� �� �ʱ�ȭ
	virtual void InitMovement() = 0;

	// �� ���ع��� �����̴� ����� ����
	virtual void Movement(float DeltaTime) = 0;

	// ���ع� Ÿ��
	virtual FName GetTypeName() const = 0;
};

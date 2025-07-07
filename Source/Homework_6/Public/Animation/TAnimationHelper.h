#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAnimationTransitionType : uint8
{
	LINEAR = 0  UMETA(DisplayName = "LINEAR"),
	EASE_IN_OUT UMETA(DisplayName = "EASE IN, EASE OUT")
};

UENUM(BlueprintType)
enum class EAnimationTravelType : uint8
{
	PING_PONG = 0 UMETA(DisplayName = "[0, 1] Ping Pong"),
	GO_AND_RESET  UMETA(DisplayName = "[0, 1] 0 to 1, Reset")
};

// 시간에 따른 변화를 구현하기 위한 클래스
template<typename T>
class HOMEWORK_6_API TAnimationHelper
{
public:
	TAnimationHelper() : Source(), Destination()
	{
		Distance = 0;
		Timer = 0;
		Speed = 0;
		Offset = 0;
	}

	TAnimationHelper(T Zero) : TAnimationHelper()
	{
		Source = Zero;
		Destination = Zero;
	}

	void Init(T Src, T Dest, float _Speed, float _Offset)
	{
		Source = Src;
		Destination = Dest;
		Distance = GetDistance();
		Speed = _Speed;
		Timer = (Distance / Speed) * _Offset;
	}

	// DeltaTime만큼 시간이 흐른 뒤의 변화 정보를 가져온다
	T GetNext(float DeltaTime, EAnimationTravelType TravelType, EAnimationTransitionType TransitionType)
	{
		Timer += DeltaTime;
		float Alpha = GetAlpha(TravelType, TransitionType);
		return LinearInterpolation(Source, Destination, Alpha);
	}

	// For Manual Animation: 애니메이션 수동 조작
	T GetManual(float Alpha, EAnimationTravelType TravelType, EAnimationTransitionType TransitionType)
	{
		return LinearInterpolation(Source, Destination, Alpha);
	}

protected:
	T Source;
	T Destination;
	float Distance;
	float Timer;
	float Speed;
	float Offset;

	T LinearInterpolation(T& A, T& B, float Alpha);
	float GetAlpha(EAnimationTravelType TravelType, EAnimationTransitionType TransitionType);
	float GetDistance();
};

template<typename T>
inline float TAnimationHelper<T>::GetDistance()
{
	return -1;
}

template<>
inline float TAnimationHelper<FVector>::GetDistance()
{
	return (Destination - Source).Length();
}

template<>
inline float TAnimationHelper<FRotator>::GetDistance()
{
	FRotator RotateTo = Destination - Source;
	return FMath::Sqrt(
		RotateTo.Pitch * RotateTo.Pitch +
		RotateTo.Yaw * RotateTo.Yaw +
		RotateTo.Roll * RotateTo.Roll);
}

template<typename T>
inline float TAnimationHelper<T>::GetAlpha(EAnimationTravelType TravelType, EAnimationTransitionType TransitionType)
{
	float Alpha = 0;
	float TravelTime = Distance / Speed;
	if (TravelType == EAnimationTravelType::GO_AND_RESET)
	{
		if (Timer > TravelTime)
		{
			Timer -= (TravelTime);
		}
		Alpha = Timer / TravelTime;
	}
	else // TravelType == EObstacleTravelType::PING_PONG
	{
		// Simulate Ping-Ping [0, 1]
		if (Timer > TravelTime * 2.0f)
		{
			Timer -= (TravelTime * 2.0f);
		}
		float PingPong = -FMath::Abs(1.0f - Timer / TravelTime) + 1.0f;
		Alpha = PingPong;

		if (TransitionType == EAnimationTransitionType::EASE_IN_OUT)
		{
			Alpha = (1.0f - FMath::Cos(UE_PI * PingPong)) / 2.0f;
		}
	}
	return Alpha;
}

template<typename T>
inline T TAnimationHelper<T>::LinearInterpolation(T& A, T& B, float Alpha)
{
	return FMath::Lerp(A, B, Alpha);
}

template<>
inline FRotator TAnimationHelper<FRotator>::LinearInterpolation(FRotator& A, FRotator& B, float Alpha)
{
	FRotator NewRotation;
	NewRotation.Pitch = FMath::Lerp(A.Pitch, B.Pitch, Alpha);
	NewRotation.Yaw = FMath::Lerp(A.Yaw, B.Yaw, Alpha);
	NewRotation.Roll = FMath::Lerp(A.Roll, B.Roll, Alpha);
	return NewRotation;
}

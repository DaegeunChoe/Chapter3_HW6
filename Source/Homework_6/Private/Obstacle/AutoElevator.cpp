#include "Obstacle/AutoElevator.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"


AAutoElevator::AAutoElevator() : AnimationHelper(FVector::ZeroVector)
{
 	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	UpDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("UpDirection"));
	UpDirection->SetRelativeRotation(FRotator(90, 0, 0));
	UpDirection->SetupAttachment(SceneRoot);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(StaticMeshComp);

	MoveSpeed = 500;
	MoveDistance = 100;
	WaitDuration = 2;

	AnimationInterval = 1.0f / 60.0f;
	AnimationTime = 0;

	Source = FVector::ZeroVector;
	Destination = Source;
	Destination.Z += MoveDistance;
}


void AAutoElevator::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAutoElevator::OnEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AAutoElevator::OnExit);
	AnimationTime = 0;
	Source = GetActorLocation();
	Destination = Source;
	Destination.Z += MoveDistance;
}

void AAutoElevator::OnEnter(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 즉시 상승 시작
	UWorld* World = GetWorld();
	if (World)
	{
		// 대기 타이머 해제
		World->GetTimerManager().ClearTimer(WaitTimer);

		// 중간 위치 계산
		float CurrentTime = (GetActorLocation() - Source).Length() / MoveSpeed;
		AnimationTime = CurrentTime;

		AnimationHelper.Init(Source, Destination, MoveSpeed, 0);
		World->GetTimerManager().SetTimer(MoveAnimationTimer, this, &AAutoElevator::UpdateMoveAnimation, AnimationInterval, true);
		UpdateMoveAnimation();
	}
}

void AAutoElevator::OnEndWait()
{
	// 하강 시작
	UWorld* World = GetWorld();
	if (World)
	{
		// 중간 위치 계산
		float CurrentTime = (GetActorLocation() - Destination).Length() / MoveSpeed;
		AnimationTime = CurrentTime;

		AnimationHelper.Init(Destination, Source, MoveSpeed, 0);
		World->GetTimerManager().SetTimer(MoveAnimationTimer, this, &AAutoElevator::UpdateMoveAnimation, AnimationInterval, true);
		UpdateMoveAnimation();
	}
}

void AAutoElevator::OnExit(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	UWorld* World = GetWorld();
	if (World)
	{
		// 즉시 움직임 정지
		World->GetTimerManager().ClearTimer(MoveAnimationTimer);

		// 대기 타이머 가동
		World->GetTimerManager().SetTimer(WaitTimer, this, &AAutoElevator::OnEndWait, WaitDuration, false);
	}
}

void AAutoElevator::UpdateMoveAnimation()
{
	float TotalTime = MoveDistance / MoveSpeed;
	float Alpha = AnimationTime / TotalTime;
	bool bIsEnd = false;
	if (Alpha > 1)
	{
		bIsEnd = true;
		Alpha = 1;
	}
	AnimationTime += AnimationInterval;

	FVector NewLocation = AnimationHelper.GetManual(Alpha, EAnimationTravelType::GO_AND_RESET, EAnimationTransitionType::EASE_IN_OUT);
	SetActorLocation(NewLocation);
	
	if (bIsEnd)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->GetTimerManager().ClearTimer(MoveAnimationTimer);
			return;
		}
	}
}





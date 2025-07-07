#include "Obstacle/RotateObstacle.h"
#include "Components/ArrowComponent.h"

ARotateObstacle::ARotateObstacle() : AnimationHelper(FRotator::ZeroRotator)
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	YawAxis = CreateDefaultSubobject<UArrowComponent>(TEXT("YawAxis"));
	YawAxis->SetRelativeRotation(FRotator(90, 0, 0));
	YawAxis->SetupAttachment(SceneRoot);

	TransitionType = EAnimationTransitionType::LINEAR;
	TravelType = EAnimationTravelType::GO_AND_RESET;
	RotateTo = FRotator::ZeroRotator;
	Offset = 0;
	AngleSpeed = 90.0f;
}

void ARotateObstacle::BeginPlay()
{
	Super::BeginPlay();
	InitMovement();
}

void ARotateObstacle::Movement(float DeltaTime)
{
	FRotator NewRotation = AnimationHelper.GetNext(DeltaTime, TravelType, TransitionType);
	SetActorRelativeRotation(NewRotation);
}

void ARotateObstacle::Tick(float DeltaTime)
{
	if (ShouldMove())
	{
		Movement(DeltaTime);
	}
}

void ARotateObstacle::InitMovement()
{
	AnimationHelper.Init(GetActorRotation(), GetActorRotation() + RotateTo, AngleSpeed, Offset);
}

FName ARotateObstacle::GetTypeName() const
{
	return TEXT("RotateObstacle");
}


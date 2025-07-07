#include "Obstacle/MoveObstacle.h"
#include "Components/ArrowComponent.h"

AMoveObstacle::AMoveObstacle() : AnimationHelper(FVector::ZeroVector)
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardDirection"));
	ForwardArrow->SetupAttachment(SceneRoot);

	TravelType = EAnimationTravelType::PING_PONG;
	TransitionType = EAnimationTransitionType::LINEAR;
	MoveTo = FVector::ZeroVector;
	Offset = 0.0f;
	Speed = 100.0f;
}

void AMoveObstacle::BeginPlay()
{
	Super::BeginPlay();
	InitMovement();
}

void AMoveObstacle::Movement(float DeltaTime)
{
	FVector NewLocation = AnimationHelper.GetNext(DeltaTime, TravelType, TransitionType);
	SetActorLocation(NewLocation);
}

FName AMoveObstacle::GetTypeName() const
{
	return TEXT("MoveObstacle");
}

void AMoveObstacle::Tick(float DeltaTime)
{
	if (ShouldMove())
	{
		Movement(DeltaTime);
	}
}

void AMoveObstacle::InitMovement()
{
	FVector WorldMoveTo = \
		GetActorForwardVector() * MoveTo.X +
		GetActorRightVector() * MoveTo.Y +
		GetActorUpVector() * MoveTo.Z;

	AnimationHelper.Init(GetActorLocation(), GetActorLocation() + WorldMoveTo, Speed, Offset);
}


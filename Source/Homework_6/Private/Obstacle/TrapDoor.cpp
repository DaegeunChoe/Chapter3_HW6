#include "Obstacle/TrapDoor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ATrapDoor::ATrapDoor() : OpenLeftHelper(FRotator::ZeroRotator), OpenRightHelper(FRotator::ZeroRotator)
{
 	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	DoorLeftAxis = CreateDefaultSubobject<USceneComponent>(TEXT("DoorLeftAxis"));
	DoorLeftAxis->SetupAttachment(SceneRoot);

	DoorRightAxis = CreateDefaultSubobject<USceneComponent>(TEXT("DoorRightAxis"));
	DoorRightAxis->SetupAttachment(SceneRoot);

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(DoorLeftAxis);

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(DoorRightAxis);

	DropDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("DropDirection"));
	DropDirection->SetupAttachment(SceneRoot);

	TrapTrigerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrigerBox"));
	TrapTrigerBox->SetupAttachment(SceneRoot);

	TrapDelay = 1;
	AngleSpeed = 90;
	AngleOpen = 90;

	AnimationInterval = 1.0f / 60.0f;
	AnimationTime = 0;

	bIsActivated = false;
}

void ATrapDoor::BeginPlay()
{
	Super::BeginPlay();

	TrapTrigerBox->OnComponentBeginOverlap.AddDynamic(this, &ATrapDoor::OnBeginOverlap);
	AnimationTime = 0;
}

void ATrapDoor::OnBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated)
	{
		UWorld* World = GetWorld();
		if (World && TrapDelay > 0)
		{
			bIsActivated = true;
			World->GetTimerManager().SetTimer(TrapTimer, this, &ATrapDoor::OnActivate, TrapDelay, false);
		}
	}
}

void ATrapDoor::OnActivate()
{
	UWorld* World = GetWorld();
	if (World)
	{
		AnimationTime = 0;
		FRotator SrcLeft = DoorLeftAxis->GetRelativeRotation();
		FRotator SrcRight = DoorRightAxis->GetRelativeRotation();
		OpenLeftHelper.Init(SrcLeft, SrcLeft + FRotator(0, 0, AngleOpen), AngleSpeed, 0);
		OpenRightHelper.Init(SrcRight, SrcRight + FRotator(0, 0, AngleOpen), AngleSpeed, 0);
		World->GetTimerManager().SetTimer(OpenAnimationTimer, this, &ATrapDoor::OpenAnimationUpdate, AnimationInterval, true);
		OpenAnimationUpdate();
	}
}

void ATrapDoor::OpenAnimationUpdate()
{
	float TotalTime = AngleOpen / AngleSpeed;
	float Alpha = AnimationTime / TotalTime;
	bool bIsEnd = false;
	if (Alpha > 1)
	{
		bIsEnd = true;
		Alpha = 1;
	}
	AnimationTime += AnimationInterval;
	FRotator NewLeftRotator = OpenLeftHelper.GetManual(Alpha, EAnimationTravelType::GO_AND_RESET, EAnimationTransitionType::EASE_IN_OUT);
	FRotator NewRightRotator = OpenRightHelper.GetManual(Alpha, EAnimationTravelType::GO_AND_RESET, EAnimationTransitionType::EASE_IN_OUT);
	DoorLeftAxis->SetRelativeRotation(NewLeftRotator);
	DoorRightAxis->SetRelativeRotation(NewRightRotator);

	if (bIsEnd)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->GetTimerManager().ClearTimer(OpenAnimationTimer);
			return;
		}
	}
}
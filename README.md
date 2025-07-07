# Chapter3_HW6
내일배움캠프 Chapter3 과제6번 제출용 저장소

## Youtube
[![ALTTEXT](https://img.youtube.com/vi/wkfo8naCIzA/0.jpg)](https://www.youtube.com/watch?v=wkfo8naCIzA)

- 영상 앞부분에 '에디터의 Details 패널을 이용하여 변수를 수정하는 장면'이 있습니다.
- 회전하는 장애물은 랜덤으로 생성됩니다.
- 바닥이 열리는 문 함정의 경우, 문이 열리는 함정이 랜덤으로 정해집니다.

## 소스 코드 설명

- Source/Homework_6/Public/
  * Animation/
    - TAnimationHelper.h
      * 시간에 따라 변화하는 것을 표현하기 위한 클래스
      * Source와 Destination 사이를 Alpha 값을 이용하여 보간한다.
      * Tick()의 DetlaTime을 이용하여 Alpha 값을 변화시킨다.
      * template type T가 FVector면 이동하고, FRotator이면 회전한다.
  * Game/
    - MyGameModeBase.h
    - MyGameStateBase.h
  * Obstacle/
    - ObstacleBase.h
      * 이동하는 장애물과 회전하는 장애물의 인터페이스
    - MoveObstacle.h
      * 직선으로 이동하는 장애물
      * Tick()을 사용한다
      * 이동 방향 및 거리, 이동 속력, 오프셋, 이동 방법, 그리고 전환 방법을 설정할 수 있다
    - RotateObstacle.h
      * 회전하는 장애물
      * Tick()을 사용한다
      * 회전 방향 및 각도, 각속력, 오프셋, 회전 방법 및 전환 방법을 설정할 수 있다
    - AutoElevator.h
      * 자동 엘레베이터
      * 캐릭터가 올라가면 즉시 상승한다
      * 캐릭터가 내리면, 일정 시간 기다린다. 기다리는 시간이 끝나면, 원위치를 향해 하강한다
      * SetTimer()를 사용한다
      * 최대 높이와 속력을 설정할 수 있다
    - TrapDoor.h
      * 아래로 문이 열리는 함정
      * 캐릭터가 올라오면, 일정 시간 이후 바닥이 열린다.
      * SetTimer()를 사용한다
      * 바닥이 열리기 전 딜레이, 바닥 문이 열리는 각속력, 바닥 문이 열리는 정도를 설정할 수 있다.
  * Player/
    - MyCharacter.h
    - MyPlayerController.h
  * Spawner/
    - BinaryRandomSpawner.h
      * 2N개의 액터를 생성하는 스포너
    - BinaryTrapDoorSpawner.h
      * 2N개의 트랩도어를 생성하고, 두 개 중 하나의 함정이 동작하도록 랜덤하게 설정하는 스포너
    - BoxRandomSpawner.h
      * 정해진 영역 안에 N개의 물체를 생성하는 스포너
    - GearRandomSpawner.h
      * 정해진 영역 안에 회전하는 장애물 N개를 생성하고, 회전 속도와 방향을 랜덤하게 설정하는 스포너

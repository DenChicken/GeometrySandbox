// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h" // M2L19
// M2L18 3: подключаем хедеры статик меша и камеры
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/Controller.h"

// M2L17 8: создаём паунам свою категорию логирования
DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)


// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// M2L17 7: создаём компонент SceneComponent, который мы сделаем корневым при помощи SetRootComponent()
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	// M2L18 4: создаём два компонента по аналогии со СценКомпонент
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	// M2L18 5: добавим компоненты в иерархию компонентов нашего пауна при помощи функции в SceneComponent (т.к. меш и камеры наследники)
	StaticMeshComponent->SetupAttachment(SceneComponent); // можно GetRootComponent(), т.к. SceneComponent корневой 
	CameraComponent->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// M2L17 10: каждый тик проверяем, есть ли движение 
	if (!VelocityVector.IsZero())
	{
		// M2L17 11: Создаём локальную константу для вычисления текущего положения пауна
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;

		// M2L17 12: Устанавливаем новое положение нашему пауну
		SetActorLocation(NewLocation);

		// M2L18 25: после смены пауна вручную останавливаем первый
		VelocityVector = FVector::ZeroVector;
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// M2L17 9: чтобы функции срабатывали при срабатывании мэпингов (нажатиях), необходимо их забиндить при помощи функций
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	}
} 

void ASandboxPawn::MoveForward(float Amount)
{
	// M2L17 8: залогируем параметр Amount
	// UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount);

	// M2L17 9: Запрограммируем движение по оX (Amount = [1, -1])
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	// M2L17 8: залогируем параметр Amount
	// UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount);

	// M2L17 9: Запрограммируем движение по оY (Amount = [1, -1])
	VelocityVector.Y = Amount;

}

void ASandboxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!NewController) return;
	UE_LOG(LogSandboxPawn, Error, TEXT("%s possessed %s"), *GetName(), *NewController->GetName());
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();

	UE_LOG(LogSandboxPawn, Warning, TEXT("%s unpossessed"), *GetName());
}


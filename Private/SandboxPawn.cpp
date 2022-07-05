// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"


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
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// M2L17 9: чтобы функции срабатывали при срабатывании мэпингов (нажатиях), необходимо их забиндить при помощи функций
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
} 

void ASandboxPawn::MoveForward(float Amount)
{
	// M2L17 8: залогируем параметр Amount
	UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount);

	// M2L17 9: Запрограммируем движение по оX (Amount = [1, -1])
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	// M2L17 8: залогируем параметр Amount
	UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount);

	// M2L17 9: Запрограммируем движение по оY (Amount = [1, -1])
	VelocityVector.Y = Amount;

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"


// M2L17 8: ������ ������ ���� ��������� �����������
DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)


// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// M2L17 7: ������ ��������� SceneComponent, ������� �� ������� �������� ��� ������ SetRootComponent()
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

	// M2L17 10: ������ ��� ���������, ���� �� �������� 
	if (!VelocityVector.IsZero())
	{
		// M2L17 11: ������ ��������� ��������� ��� ���������� �������� ��������� �����
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;

		// M2L17 12: ������������� ����� ��������� ������ �����
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// M2L17 9: ����� ������� ����������� ��� ������������ �������� (��������), ���������� �� ��������� ��� ������ �������
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
} 

void ASandboxPawn::MoveForward(float Amount)
{
	// M2L17 8: ���������� �������� Amount
	UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount);

	// M2L17 9: ��������������� �������� �� �X (Amount = [1, -1])
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	// M2L17 8: ���������� �������� Amount
	UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount);

	// M2L17 9: ��������������� �������� �� �Y (Amount = [1, -1])
	VelocityVector.Y = Amount;

}

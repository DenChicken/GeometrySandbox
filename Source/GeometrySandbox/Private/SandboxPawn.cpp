// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h" // M2L19
// M2L18 3: ���������� ������ ������ ���� � ������
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/Controller.h"

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

	// M2L18 4: ������ ��� ���������� �� �������� �� �������������
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	// M2L18 5: ������� ���������� � �������� ����������� ������ ����� ��� ������ ������� � SceneComponent (�.�. ��� � ������ ����������)
	StaticMeshComponent->SetupAttachment(SceneComponent); // ����� GetRootComponent(), �.�. SceneComponent �������� 
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

	// M2L17 10: ������ ��� ���������, ���� �� �������� 
	if (!VelocityVector.IsZero())
	{
		// M2L17 11: ������ ��������� ��������� ��� ���������� �������� ��������� �����
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;

		// M2L17 12: ������������� ����� ��������� ������ �����
		SetActorLocation(NewLocation);

		// M2L18 25: ����� ����� ����� ������� ������������� ������
		VelocityVector = FVector::ZeroVector;
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// M2L17 9: ����� ������� ����������� ��� ������������ �������� (��������), ���������� �� ��������� ��� ������ �������
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	}
} 

void ASandboxPawn::MoveForward(float Amount)
{
	// M2L17 8: ���������� �������� Amount
	// UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount);

	// M2L17 9: ��������������� �������� �� �X (Amount = [1, -1])
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	// M2L17 8: ���������� �������� Amount
	// UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount);

	// M2L17 9: ��������������� �������� �� �Y (Amount = [1, -1])
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


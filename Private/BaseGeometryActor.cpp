// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
// ���.�. ��� ������� � ����������� ������� GEngine
#include "Engine/Engine.h"
// M2L12: ��������� ���. �. ��� ���� UMaterialInstanceDynamic, ����� �������� � ������
#include "Materials/MaterialInstanceDynamic.h"
// M2L13: ������������ ���� ��� �������
#include "TimerManager.h"


// �������� ����������� ��������� ����������� (��������, ��.���, ��.���.������.)
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)
// UE_LOG(LogBaseGeometry, Display, TEXT("info")); // ������ �������������

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// M2L10: ������ ��� ��������� ��� ������ ��������� �������, ������� ��������� �������� ���� UStaticMeshComponent � ���������� ��������� ������� ����
	// M2L10: ��������� 2 ���������: ��� ����������, � ������ ���� ��� ������� (�� ��������� false)
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	// M2L10: ������ �������� ��������� ������ ������. ����� ������� �� �����������, ��� ������������� ������ ����� ��������� � �������������� ����������
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	// Super = AActor (alias)
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	// printStringTypes();		// M2L8
	// printTypes();			// M2L7
	// printTransform();		// M2L10

	/*
		M2L15 5: 
			�������� ��������� ������� � ���� ������ �� ����� � ������������ ����������
			������������� ������ � ��������� �������� ���� ����� �����, ����� ��� ����������.
			�� ��� ������������ �������� ��� ������ ������� SetTimer, ��������� � �� ������
			�� ������� ABaseGeometryActor::OnTimerFired
	*/ 


	SetColor(GeometryData.Color);				// M2L122

	// M2L13: ���������� ������ TimerManager ��� ������ ������� SetTimer(), ���: ������ �������� - ���������� �������,
	// M2L13: ������ �������� - ��������� �� ������, �� ������� �� ����� �������� ������� ��� ������������ �������, 
	// M2L13: ������ �������� - ������ �� �������, ������� ����� ����������, 4 ��� - ������� ������� � ��������, 5� - ������������� ������� (true - ���.)
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// M2L15 24: ���������� �� ����������� ������
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor %s is dead"), *GetName());

	// M2L15 23: �������� ������� �������� ������, ����� �� �������� ����������������
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();	
}

void ABaseGeometryActor::PrintTypes()
{
	// ������ �����������. 1� - �������� ��������� �����������, 2� - ����� �����������, 3� - ������ ������ (�������� ������ ����� ������ TEXT()
	// UE_LOG(LogBaseGeometry, Warning, TEXT("Hello Unreal!"));

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());

	// ��� ����� ����� ������������ ������� %d ��� %i, ��� 
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);

	// ��� ����� � ��. �. ����. ������� %f (��������� .2 ����������, ��� �� ����� ������� 2 ����� ����� �����)
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %.2f"), Health);

	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Connor";
	// ��� �� ����� �������� � FString, ������� �������� ������ char ����� ���������
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	if (GEngine)
	{
		// ������� ��������� ������ ���� (���������� ���� ���������: -1 - ��� �����; ���-�� ������; ���� ���������; ������ ���� FString)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Name);
		// ��������� ��� ��������� - ������� ������ (������� ������� �����) � ����� ��������� (��������� ��������������� � 1.5 ����)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::PrintTransform()
{
	// M2L10: ������� ������ � ������������� ������ �� ����
	FTransform Transform = GetActorTransform();
	// M2L10: ������� ������ � ��������� ���������� ������� ������ Transform
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale: %s"), *Scale.ToString());


	UE_LOG(LogBaseGeometry, Error, TEXT("Hman transform: %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::HandleMovement()
{
	// M2L11: ������� ����� �� ������ �����
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		// M2L10: �������� ������� �� ���������: z = z0 + amplitude * sin(freq * t);
		FVector CurrentLocation = GetActorLocation();

		if (GetWorld())
		{
			// M2L10: �������� ����� � ������ ���� ����� ���������� ��������� �� ���
			float Time = GetWorld()->GetTimeSeconds();

			// M2L10: ���������� � Z ���������� ���������� CurrentLocation � �������� � �� ������ ���������
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			// M2L10: ��������� ������� ������
			SetActorLocation(CurrentLocation);
		}
		
	} break;

	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	// M2L12: �������� ������ � ������ ��������� �� editor UE4 (�������� - ������ ���������)
	// M2L12: �� ������ ��������� ������� �������, ������������� ��� ���������� � ���������� �� ���� ���������
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		// M2L12: ���� DynMaterial ��������, �������� ������ � ��������� "Color" ��������� � ������ ���� Yellow
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	// M2L13: ���� ������� ������� ������ ��� ����� ������������� ��������, ������ ����
	if (++TimerCount <= MaxTimerCount)
	{
		// M2L13: �������� ���������� NewColor, ���������� ��������� ����, ��� ������ ����������� ������� MakeRandomColor()
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("Timer count: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);

		// M2L15 12: ������������ ������� �������� ��� ��������� ����� ��������� (Broadcast �������� ��� ����������� �� ������� �������)
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	// M2L13: ���� ������� ������ ������������� ��������, ��������� ������ ����� TimerHandle
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);

		// M2L15 13: ������ ������� ����� ����������� �����, ����� ������ �������� ������
		OnTimerFinished.Broadcast(this);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"		// ��������� �.�. ��� ��������� ��������� �� ���


// M2L15 15: �������� ���� ���. ��������� ��� Hub-������
DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)


// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	// DoActorSpawn1();
	// DoActorSpawn2();
	// DoActorSpawn3();
	DoActorSpawn4();
	
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// M2L20 4: ������ ����� ����� �������� ���������� � ����� ����������
	UE_LOG(LogGeometryHub, Warning, TEXT("property pointer %i, is valid %i"), PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Error, TEXT("none property pointer %i, is valid %i"), NonePropertyActor != nullptr, IsValid(NonePropertyActor));
}

void AGeometryHubActor::DoActorSpawn1()
{
	// M2L14 1: ������� ��������� �� ��� ����
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 8: �������� 10 �������
		for (int32 i = 0; i < 10; ++i)
		{
			// M2L14 7: �������� ������ �������������, ������� ����� ������������� ������ �� �����
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));

			// M2L14 2: ��������� ������ � ���. ������ ���, ��������� ������������� � ���. ���������
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				// M2L14 9: �������� ������ Data � �������� ��� ������� Geometry
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	// M2L14 1: ������� ��������� �� ��� ����
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 11: ���������� ����� �������
		for (int32 i = 0; i < 10; ++i)
		{
			// M2L14 7: �������� ������ �������������, ������� ����� ������������� ������ �� �����
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 800.0f));

			// M2L14 2: ��������� ������ � ���. ������ ���, ��������� ������������� � ���. ���������
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				// M2L14 9: �������� ������ Data � �������� ��� ������� Geometry
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				// M2L14 12: ����� ��������� ������� �������� ������� BeginPlay
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	// M2L14 1: ������� ��������� �� ��� ����
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 15: ��������� ������� � ����������� �� ����������, ������� ��������� � ������� GeometryPayloads
		for (const FGeometryPayload Payload : GeometryPayloads)
		{
			ABaseGeometryActor* Geometry =
				World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

			if (Geometry)
			{
				Geometry->SetGeometryData(Payload.Data);

				// M2L15 17: ����� ���, ��� ��������� �����, ������ ���� ����� �������
				// M2L15 18: ����� �������� ������� ������������� ��������, ���������� ��������������� �������� AddDynamic()
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				// M2L15 18: ��� ��������������� �������� ������������ ������� AddUObject
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);

				Geometry->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	// M2L15 16: ������� ���������� �� ������
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s, Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	// M2L15 16: ������� ���������� �� ������
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	// M2L15 20: �������� ������ �������������� ��������� ABaseGeometryActor � AActor (�����������)
	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;
	else
		UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude: %f"), Geometry->GetGeometryData().Amplitude);

	// M2L15 21: �������� ������ �� ����� (Destroy/SetLifeSpan, ������ ������� ����� ���������� ����� � ���)
	Geometry->Destroy();
	// Geometry->SetLifeSpan(2.0f);
}

void AGeometryHubActor::DoActorSpawn4()
{
	if (!GetWorld()) return;

	// M2L20 3: �������� ���� ������� � ��������� �� ��� ���� ���������
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 300.0f, 300.0f));
	NonePropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 700.0f, 300.0f));
	PropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}
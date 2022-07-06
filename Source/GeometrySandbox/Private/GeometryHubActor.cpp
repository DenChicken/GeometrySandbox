// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"		// Добавляем з.ф. для получения указателя на мир


// M2L15 15: Создадим свою лог. категорию для Hub-актора
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

	// M2L20 4: каждый фрейм будем выводить информацию о наших указателях
	UE_LOG(LogGeometryHub, Warning, TEXT("property pointer %i, is valid %i"), PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Error, TEXT("none property pointer %i, is valid %i"), NonePropertyActor != nullptr, IsValid(NonePropertyActor));
}

void AGeometryHubActor::DoActorSpawn1()
{
	// M2L14 1: Получим указатель на мир игры
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 8: Создадим 10 акторов
		for (int32 i = 0; i < 10; ++i)
		{
			// M2L14 7: Создадим объект трансформации, который будет присваиваться актору на сцене
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));

			// M2L14 2: Заспавним актора в мир. Укажем тип, параметры трансформации и доп. настройки
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				// M2L14 9: Создадим объект Data и присвоим его объекту Geometry
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	// M2L14 1: Получим указатель на мир игры
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 11: Отложенный вызов акторов
		for (int32 i = 0; i < 10; ++i)
		{
			// M2L14 7: Создадим объект трансформации, который будет присваиваться актору на сцене
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 800.0f));

			// M2L14 2: Заспавним актора в мир. Укажем тип, параметры трансформации и доп. настройки
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				// M2L14 9: Создадим объект Data и присвоим его объекту Geometry
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				// M2L14 12: После настройки объекта запустим функцию BeginPlay
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	// M2L14 1: Получим указатель на мир игры
	UWorld* World = GetWorld();
	if (World)
	{
		// M2L14 15: Заспауним акторов в зависимости от информации, которая находится в массиве GeometryPayloads
		for (const FGeometryPayload Payload : GeometryPayloads)
		{
			ABaseGeometryActor* Geometry =
				World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

			if (Geometry)
			{
				Geometry->SetGeometryData(Payload.Data);

				// M2L15 17: Перед тем, как завершить спаун, делаем бинд наших функций
				// M2L15 18: Чтобы добавить функцию динамическому делегату, необходимо воспользоваться макросом AddDynamic()
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				// M2L15 18: Для нединамического делегата используется функция AddUObject
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);

				Geometry->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	// M2L15 16: Выводим информацию об акторе
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s, Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	// M2L15 16: Выводим информацию об акторе
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	// M2L15 20: Проведем ручное преобразование указателя ABaseGeometryActor в AActor (даункастинг)
	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;
	else
		UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude: %f"), Geometry->GetGeometryData().Amplitude);

	// M2L15 21: Удаление актора со сцены (Destroy/SetLifeSpan, вторая удаляет через отведенное время в сек)
	Geometry->Destroy();
	// Geometry->SetLifeSpan(2.0f);
}

void AGeometryHubActor::DoActorSpawn4()
{
	if (!GetWorld()) return;

	// M2L20 3: создадим двух акторов и установим на них наши указатели
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 300.0f, 300.0f));
	NonePropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 700.0f, 300.0f));
	PropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
// Заг.ф. для доступа к глобальному объекту GEngine
#include "Engine/Engine.h"
// M2L12: Подключим заг. ф. для типа UMaterialInstanceDynamic, чтобы работать с цветом
#include "Materials/MaterialInstanceDynamic.h"
// M2L13: Заголовочный файл для таймера
#include "TimerManager.h"


// Создадим собственную категорию логирования (название, ур.лог, ур.лог.компил.)
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)
// UE_LOG(LogBaseGeometry, Display, TEXT("info")); // пример использования

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// M2L10: создаём наш компонент при помощи шаблонной функции, которая принимает параметр типа UStaticMeshComponent и возвращает указатель данного типа
	// M2L10: принимает 2 аргумента: имя компонента, а второй пока что неважен (по умолчанию false)
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	// M2L10: укажем корневой компонент нашему актору. Таким образом мы декларируем, что трансформация актора будет совпадать с трансформацией компонента
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
			Делегаты позволяют хранить в себе ссылку на метод с определенной сигнатурой
			произвольного класса и позволяют вызывать этот метод тогда, когда это необходимо.
			Мы уже использовали делегаты при вызове функции SetTimer, передавая в неё ссылку
			на функцию ABaseGeometryActor::OnTimerFired
	*/ 


	SetColor(GeometryData.Color);				// M2L122

	// M2L13: Возвращаем объект TimerManager при помощи функции SetTimer(), где: первый аргумент - дискриптор таймера,
	// M2L13: второй аргумент - указатель на объект, на который мы хотим вызывать функцию при срабатывании таймера, 
	// M2L13: третий аргумент - ссылка на функцию, которая будет вызываться, 4 арг - частота таймера в секундах, 5й - зацикленность таймера (true - зац.)
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// M2L15 24: Уведомляем об уничтожении актора
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor %s is dead"), *GetName());

	// M2L15 23: Вызываем функцию базового класса, чтобы не потерять функциональность
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
	// Макрос логирования. 1п - название категории логирования, 2п - стиль логирования, 3п - строка вывода (передаем строку через макрос TEXT()
	// UE_LOG(LogBaseGeometry, Warning, TEXT("Hello Unreal!"));

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());

	// Для целых чисел спецификатор формата %d или %i, для 
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);

	// Для чисел с пл. т. спец. формата %f (приставка .2 показывает, что мы хотим вывести 2 знака после точки)
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %.2f"), Health);

	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Connor";
	// Лог не умеет работать с FString, поэтому передаем массив char через указатель
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	if (GEngine)
	{
		// Выведем сообщение поверх игры (уникальный ключ сообщения: -1 - нет ключа; кол-во секунд; цвет сообщения; строка типа FString)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Name);
		// Последние два аргумента - порядок вывода (сначала выводим статы) и скейл сообщения (увеличили пропорционально в 1.5 раза)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::PrintTransform()
{
	// M2L10: Получим доступ к трансформации актора из кода
	FTransform Transform = GetActorTransform();
	// M2L10: Получим доступ к некоторым переменным объекта класса Transform
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
	// M2L11: Сделаем свитч по нашему энаму
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		// M2L10: Движение акторов по синусоиде: z = z0 + amplitude * sin(freq * t);
		FVector CurrentLocation = GetActorLocation();

		if (GetWorld())
		{
			// M2L10: Получаем время с начала игры через глобальный указатель на мир
			float Time = GetWorld()->GetTimeSeconds();

			// M2L10: Обращаемся к Z координате переменной CurrentLocation и изменяем её по закону синусоиды
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			// M2L10: Обновляем позицию актора
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
	// M2L12: Получаем доступ к нашему материалу из editor UE4 (аргумент - индекс материала)
	// M2L12: На основе материала создает инстанс, устанавливает его компоненту и возвращает не него указатель
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		// M2L12: Если DynMaterial создался, получаем доступ к параметру "Color" материала и ставим цвет Yellow
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	// M2L13: Если счётчик таймера меньше или равен максимальному значению, меняем цвет
	if (++TimerCount <= MaxTimerCount)
	{
		// M2L13: Создадим переменную NewColor, содержащую случайный цвет, при помощи статической функции MakeRandomColor()
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("Timer count: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);

		// M2L15 12: Срабатывание первого делегата при изменении цвета материала (Broadcast вызывает все подписанные на делегат функции)
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	// M2L13: Если счётчик больше максимального значения, выключаем таймер через TimerHandle
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);

		// M2L15 13: Второй делегат будет срабатывать тогда, когда таймер закончил работу
		OnTimerFinished.Broadcast(this);
	}
}


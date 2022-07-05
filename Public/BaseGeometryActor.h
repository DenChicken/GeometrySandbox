// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
	Определяем:
	1. Базовые типы, константы, инструменты для логирования;
	2. Заг. файл класса AActor;
	4. M2L10: подключаем заг. файл компонента геометрии
	3. Автоматически сгенерировнный движком хедер для данного AActor (идет последним).
*/
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"


// M2L15 6: Объявим наш делегат при помощи макроса DECLARE_...DELEGATE() (их там очень много, см. F12)
// M2L15 7: На ...DYNAMIC_MULTICAST могут подписаться несколько клиентов
// M2L15 8: Имя делегата - FOnColorChanged; 2арг. - тип 1го пар-ра, 3арг. - имя 1го, 4арг. - тип 2го, 5арг. - имя 2го
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);

// M2L15 9: Объявляем второй делегат без DYNAMIC (доступен только в С++, т.е. не надо указывать имя параметра)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);


// M2L11: Создаём перечисление enum с типами движений
// M2L11: Используем макрос, который расширяет наш enum. Параметр BlueprintType выводим enum в блюпринтах
// M2L11: Т.о., в едиторе мы сможем менять наше значение enum
UENUM(BlueprintType)
enum class EMovementType : uint8	// M2L11: При этом все энамы должны начинаться с E и иметь строгий тип uint8
{
	Sin,
	Static
};

// M2L11: Создадим структуру с типами движения
// M2L11: Создаем специальный макрос USTRUCT(BlueprintType) как для enum'а выше
USTRUCT(BlueprintType)
struct FGeometryData
{
	// M2L11: Об этих макросах - в конце раздела M2
	GENERATED_USTRUCT_BODY()

	// M2L10: Создаем переменные амплитуды и частоты
	// M2L15 2: Также добавим спецификатор BlueprintReadWtire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	// M2L11: Создаём переменную типа MovementType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Sin;

	// M2L12: Создаем новую переменную типа FLinearColor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	// M2L13: Переменная, отвечающая за частоту срабатывания таймера
	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate = 3.0f;
};


UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	// Компоненты - объекты с определенной функциональностью, которые мы можем добавить актору для расширения его возможностей
	// В ООП данный приём называется композицией 
	UPROPERTY(VisibleAnywhere)
	// Создадим первый компонент - указатель на объект, содержащий некоторую геометрию
	UStaticMeshComponent* BaseMesh;

	// M2L14 10: Создадим сеттер для установки параметров объекта
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	// M2L15 3: Функция, возвращающая копию объекта геометрии
	// M2L15 4: Сделаем её доступной в BP при помощи UFUNCTION()
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData;  }

	// M2L15 10: Делегаты задекларированы, теперь их нужно создать
	// M2L15 11: Чтобы на делегат OnColorChanged можно было подписаться в BP, сделаем юпроперти
	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;

	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// M2L15 22: Переопределяем виртуальную функцию EndPlay класса AActor
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// M2L11: Создаем переменную структуры типа FGeometryData
	// M2L15 1: Добавим спецификатор BlueprintReadWtire, который открывает доступ к проперти в блюпринте
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

	// Макрос, выводящий переменные в UE4 (имеет разные спецификаторы доступа):
	// EditAnywhere - доступен как в архитипе (в редакторе BluePrint), так и у инстанса (объекта на сцене)
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;		// Вместо int используем тип int32, гарантирующий корректную компиляцию для разных платформ

	// EditDefaultsOnly - доступен только в архитипе
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	// EditInstanceOnly - доступна только у инстанса
	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 34.50495f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool IsDead = false;

	// VisibleAnywhere - видима отовсюду, но не редактируется
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// M2L10: Создаем переменную, которая будет отвечать за первоначальное положение актора
	FVector InitialLocation;

	// M2L13: Создаём дескриптор таймера - переменную, которая будет однозначно идентифицировать таймер
	// M2L13: С помощью неё будем получать доступ к нашему таймеру
	FTimerHandle TimerHandle;

	// M2L13: Создадим константу, которая будет отвечать за количество переключений до остановки и счётчик переключений
	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();

	void HandleMovement();

	void SetColor(const FLinearColor& Color);

	// M2L13: Данная функция будет вызываться каждый раз, как будет срабатывать таймер
	void OnTimerFired();
};

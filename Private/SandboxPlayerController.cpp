// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
// M2L18 10: подключаем класс для импута
#include "Components/InputComponent.h"
// M2L18 15: подключим хедер для статистики
#include "Kismet/GameplayStatics.h"
// M2L18 17: подключаем хедер пауна
#include "SandboxPawn.h"


// M2L18 13: создаём паунам свою категорию логирования
DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)


void ASandboxPlayerController::SetupInputComponent()
{
	// M2L18 9: плеер контроллер также может принимать инпут
	Super::SetupInputComponent();

	if (InputComponent)
	{
		// M2L18 11: в отличие от PlayerInputCompontn, где инпут передается в виде аргумента функции, 
	// ... для InputComponent инпут представлен в виде члена класса
	// ... обратимся к InputComponent напрямую и забиндим мепинги
		InputComponent->BindAction("ChangePawn",
			IE_Pressed /*Enum*/, this, &ASandboxPlayerController::ChangePawn);
	}
}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// M2L18 16: получаем всех акторов класса ASandboxPawn в массив Pawns
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);

}

void ASandboxPlayerController::ChangePawn()
{
	// M2L18 18: если нет доступных паунов на сцене, выходим из функции
	if (Pawns.Num() <= 1) return;

	// M2L18 19: получим указатель на паун из массива в локальную переменную
	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);

	// M2L18 21: сделаем так, чтобы индекс никогда не вышел за границы массива
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();

	// M2L18 22: проверка на nullptr
	if (!CurrentPawn) return;

	// M2L18 13: уведомляем о смене пауна при нажатии на кнопку
	UE_LOG(LogSandboxPlayerController, Error, TEXT("Pawn has been changed"));

	// M2L18 23: переключим контроль над пауном при помощи функции Possess
	Possess(CurrentPawn);
}

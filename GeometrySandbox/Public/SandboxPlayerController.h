// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GEOMETRYSANDBOX_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// M2L18 8: переопределяем функцию из APlayerController
	virtual void SetupInputComponent() override;

	// M2L18 14: для смены пауна нужно получить список доступных. Сделать это можно из BeginPlay()
	// ... для каждого актора BeginPlay() свой, так что можно его переопределить
	virtual void BeginPlay() override;

	
private:
	// M2L18 17: создадим локальный массив для сбора всех акторов со сцены
	UPROPERTY()
	TArray<AActor*> Pawns;

	// M2L18 20: индекс текущего пауна
	int32 CurrentPawnIndex = 0;

	// M2L18 12: Создаём функцию для переключения между паунами
	void ChangePawn();
};

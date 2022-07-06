// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

// M2L18 2: предварительное объявление класса
class UCameraComponent;
class UStaticMeshComponent; // M2L19

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandboxPawn();

	// M2L17 4: Созаддим необходимые переменные и функции и запрограммируем их в .cpp файле
	// M2L17 5: Создадим проперти для корневого компонента - USceneComponent
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	// M2L17 5: Скорость движения пауна
	UPROPERTY(EditAnywhere)
	float Velocity = 300.0f;
	
	// M2L18 1: добавим два компонента для визуального отображения пауна камеры вьюпорта
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	// M2L18 1:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	// M2L18 24: добавим функции для обработки получения и утраты контроля над пауном
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	// M2L17 5: Создаём переменную, хранящую вектор скорости пауна
	FVector VelocityVector = FVector::ZeroVector;

	// M2L17 6: Создадим 2 функции, которые будут вызываться при срабатывании экшенов (нажатиях вперед-назад, вправо-влево)
	// M2L17 6: все подобные функции имеют один параметр типа float
	void MoveForward(float Amount);
	void MoveRight(float Amount);


};

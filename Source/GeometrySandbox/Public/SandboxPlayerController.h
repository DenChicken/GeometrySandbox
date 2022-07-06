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
	// M2L18 8: �������������� ������� �� APlayerController
	virtual void SetupInputComponent() override;

	// M2L18 14: ��� ����� ����� ����� �������� ������ ���������. ������� ��� ����� �� BeginPlay()
	// ... ��� ������� ������ BeginPlay() ����, ��� ��� ����� ��� ��������������
	virtual void BeginPlay() override;

	
private:
	// M2L18 17: �������� ��������� ������ ��� ����� ���� ������� �� �����
	UPROPERTY()
	TArray<AActor*> Pawns;

	// M2L18 20: ������ �������� �����
	int32 CurrentPawnIndex = 0;

	// M2L18 12: ������ ������� ��� ������������ ����� �������
	void ChangePawn();
};

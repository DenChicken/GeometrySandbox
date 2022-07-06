// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
// M2L18 10: ���������� ����� ��� ������
#include "Components/InputComponent.h"
// M2L18 15: ��������� ����� ��� ����������
#include "Kismet/GameplayStatics.h"
// M2L18 17: ���������� ����� �����
#include "SandboxPawn.h"


// M2L18 13: ������ ������ ���� ��������� �����������
DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)


void ASandboxPlayerController::SetupInputComponent()
{
	// M2L18 9: ����� ���������� ����� ����� ��������� �����
	Super::SetupInputComponent();

	if (InputComponent)
	{
		// M2L18 11: � ������� �� PlayerInputCompontn, ��� ����� ���������� � ���� ��������� �������, 
	// ... ��� InputComponent ����� ����������� � ���� ����� ������
	// ... ��������� � InputComponent �������� � �������� �������
		InputComponent->BindAction("ChangePawn",
			IE_Pressed /*Enum*/, this, &ASandboxPlayerController::ChangePawn);
	}
}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// M2L18 16: �������� ���� ������� ������ ASandboxPawn � ������ Pawns
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);

}

void ASandboxPlayerController::ChangePawn()
{
	// M2L18 18: ���� ��� ��������� ������ �� �����, ������� �� �������
	if (Pawns.Num() <= 1) return;

	// M2L18 19: ������� ��������� �� ���� �� ������� � ��������� ����������
	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);

	// M2L18 21: ������� ���, ����� ������ ������� �� ����� �� ������� �������
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();

	// M2L18 22: �������� �� nullptr
	if (!CurrentPawn) return;

	// M2L18 13: ���������� � ����� ����� ��� ������� �� ������
	UE_LOG(LogSandboxPlayerController, Error, TEXT("Pawn has been changed"));

	// M2L18 23: ���������� �������� ��� ������ ��� ������ ������� Possess
	Possess(CurrentPawn);
}

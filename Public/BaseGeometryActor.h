// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
	����������:
	1. ������� ����, ���������, ����������� ��� �����������;
	2. ���. ���� ������ AActor;
	4. M2L10: ���������� ���. ���� ���������� ���������
	3. ������������� �������������� ������� ����� ��� ������� AActor (���� ���������).
*/
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"


// M2L15 6: ������� ��� ������� ��� ������ ������� DECLARE_...DELEGATE() (�� ��� ����� �����, ��. F12)
// M2L15 7: �� ...DYNAMIC_MULTICAST ����� ����������� ��������� ��������
// M2L15 8: ��� �������� - FOnColorChanged; 2���. - ��� 1�� ���-��, 3���. - ��� 1��, 4���. - ��� 2��, 5���. - ��� 2��
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);

// M2L15 9: ��������� ������ ������� ��� DYNAMIC (�������� ������ � �++, �.�. �� ���� ��������� ��� ���������)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);


// M2L11: ������ ������������ enum � ������ ��������
// M2L11: ���������� ������, ������� ��������� ��� enum. �������� BlueprintType ������� enum � ����������
// M2L11: �.�., � ������� �� ������ ������ ���� �������� enum
UENUM(BlueprintType)
enum class EMovementType : uint8	// M2L11: ��� ���� ��� ����� ������ ���������� � E � ����� ������� ��� uint8
{
	Sin,
	Static
};

// M2L11: �������� ��������� � ������ ��������
// M2L11: ������� ����������� ������ USTRUCT(BlueprintType) ��� ��� enum'� ����
USTRUCT(BlueprintType)
struct FGeometryData
{
	// M2L11: �� ���� �������� - � ����� ������� M2
	GENERATED_USTRUCT_BODY()

	// M2L10: ������� ���������� ��������� � �������
	// M2L15 2: ����� ������� ������������ BlueprintReadWtire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	// M2L11: ������ ���������� ���� MovementType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Sin;

	// M2L12: ������� ����� ���������� ���� FLinearColor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	// M2L13: ����������, ���������� �� ������� ������������ �������
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

	// ���������� - ������� � ������������ �����������������, ������� �� ����� �������� ������ ��� ���������� ��� ������������
	// � ��� ������ ���� ���������� ����������� 
	UPROPERTY(VisibleAnywhere)
	// �������� ������ ��������� - ��������� �� ������, ���������� ��������� ���������
	UStaticMeshComponent* BaseMesh;

	// M2L14 10: �������� ������ ��� ��������� ���������� �������
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	// M2L15 3: �������, ������������ ����� ������� ���������
	// M2L15 4: ������� � ��������� � BP ��� ������ UFUNCTION()
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData;  }

	// M2L15 10: �������� ���������������, ������ �� ����� �������
	// M2L15 11: ����� �� ������� OnColorChanged ����� ���� ����������� � BP, ������� ���������
	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;

	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// M2L15 22: �������������� ����������� ������� EndPlay ������ AActor
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// M2L11: ������� ���������� ��������� ���� FGeometryData
	// M2L15 1: ������� ������������ BlueprintReadWtire, ������� ��������� ������ � �������� � ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

	// ������, ��������� ���������� � UE4 (����� ������ ������������� �������):
	// EditAnywhere - �������� ��� � �������� (� ��������� BluePrint), ��� � � �������� (������� �� �����)
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;		// ������ int ���������� ��� int32, ������������� ���������� ���������� ��� ������ ��������

	// EditDefaultsOnly - �������� ������ � ��������
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	// EditInstanceOnly - �������� ������ � ��������
	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 34.50495f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool IsDead = false;

	// VisibleAnywhere - ������ ��������, �� �� �������������
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// M2L10: ������� ����������, ������� ����� �������� �� �������������� ��������� ������
	FVector InitialLocation;

	// M2L13: ������ ���������� ������� - ����������, ������� ����� ���������� ���������������� ������
	// M2L13: � ������� �� ����� �������� ������ � ������ �������
	FTimerHandle TimerHandle;

	// M2L13: �������� ���������, ������� ����� �������� �� ���������� ������������ �� ��������� � ������� ������������
	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();

	void HandleMovement();

	void SetColor(const FLinearColor& Color);

	// M2L13: ������ ������� ����� ���������� ������ ���, ��� ����� ����������� ������
	void OnTimerFired();
};

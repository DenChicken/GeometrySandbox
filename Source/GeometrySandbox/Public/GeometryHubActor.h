// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"			// M2L14 6: ���������� �.�.
#include "GeometryHubActor.generated.h"


// M2L14 13: ������ ��������� ��� ��������� Data
USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	// 3 ����: ����� ��� ������, FGeometryData � ��������� �������������
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;

};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// M2L14 3: �������� �������� 
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	// M2L14 14: ������ ������ �������� ���� FGeometryPayload
	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();

	// M2L15 14: ���������� �� �������� BaseGeometryActor � ������ Hub
	// M2L15 15: �������� �������, ������� ����� ���������� ��� ������������ �����. ���������
	// M2L15 19: ������� OnColorChanged �������� UFUNCTION(), �.�. ������� ������������
	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);

	void OnTimerFinished(AActor* Actor);

};

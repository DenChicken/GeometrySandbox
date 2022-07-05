// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxGameModeBase.h"
// M2L17 2: Подключаем наш класс
#include "SandboxPawn.h"


// M2L17 1: Тело конструктора
AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase()
{
	// M2L17 3: устанавливаем (переопределяем) класс, на основе которого будет создан объект класса
	// M2L17 3: делаем это при помощи спец. указателя на класс, который м.б. получен через функцию:
	DefaultPawnClass = ASandboxPawn::StaticClass();
}
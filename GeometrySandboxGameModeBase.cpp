// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxGameModeBase.h"
// M2L17 2: ���������� ��� �����
#include "SandboxPawn.h"


// M2L17 1: ���� ������������
AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase()
{
	// M2L17 3: ������������� (��������������) �����, �� ������ �������� ����� ������ ������ ������
	// M2L17 3: ������ ��� ��� ������ ����. ��������� �� �����, ������� �.�. ������� ����� �������:
	DefaultPawnClass = ASandboxPawn::StaticClass();
}
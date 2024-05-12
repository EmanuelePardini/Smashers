// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/GameModeSelectionSystem.h"


FString UGameModeSelectionSystem::GetGm()
{
	return GmName;
}

FString UGameModeSelectionSystem::SetGm(FString SelectedGm)
{
	return GmName = SelectedGm;
}

bool UGameModeSelectionSystem::Set3d(bool Selected3d)
{
	return Is3dMode = Selected3d;
}

bool UGameModeSelectionSystem::Get3d()
{
	return Is3dMode;
}

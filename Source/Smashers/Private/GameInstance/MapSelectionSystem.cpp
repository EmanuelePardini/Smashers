// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/MapSelectionSystem.h"

FString UMapSelectionSystem::GetMap()
{
	return MapName;
}

FString UMapSelectionSystem::SetMap(FString SelectedMap)
{
	return MapName = SelectedMap;
}

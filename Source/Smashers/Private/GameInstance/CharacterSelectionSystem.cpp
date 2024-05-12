// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/CharacterSelectionSystem.h"

#include "Character/CharacterData.h"

FString UCharacterSelectionSystem::GetSmasher()
{
	return SmasherName;
}

FString UCharacterSelectionSystem::GetSmasher2()
{
	return Smasher2Name;
}

FString UCharacterSelectionSystem::SetSmasher(FString SelectedSmasher)
{
	return SmasherName = SelectedSmasher;
}

FString UCharacterSelectionSystem::SetSmasher2(FString SelectedSmasher)
{
	if(GetSmasher() == SelectedSmasher) return Smasher2Name = SelectedSmasher + SosiaPrefix;
	return Smasher2Name = SelectedSmasher;
}

FString UCharacterSelectionSystem::GetLastWinner()
{
	return LastWinnerSmasher;
}

FString UCharacterSelectionSystem::SetLastWinner(FString WinnerSmasher)
{
	return LastWinnerSmasher = WinnerSmasher;
}

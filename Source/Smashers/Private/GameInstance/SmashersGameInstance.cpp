// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/SmashersGameInstance.h"

#include "GameInstance/CharacterSelectionSystem.h"
#include "Kismet/GameplayStatics.h"

void USmashersGameInstance::LoadGameData_Implementation()
{
	ISaveGameInterface::LoadGameData_Implementation();
	if(UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGameRef = Cast<USmashersSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		
		FLevelData LoadData = SaveGameRef->GetLevelData();
		GetSubsystem<UCharacterSelectionSystem>()->SetSmasher(LoadData.CharacterName);
		UGameplayStatics::OpenLevel(GetWorld(), *LoadData.LevelName);
	}
	else
	{
		Execute_NewGameData(this, NoSavingsMenu);
	}
}

void USmashersGameInstance::SaveGameData_Implementation()
{
	ISaveGameInterface::SaveGameData_Implementation();

	UGameplayStatics::SaveGameToSlot(SaveGameRef, SlotName, 0);
}

void USmashersGameInstance::NewGameData_Implementation(const FString& FirstLevel)
{
	ISaveGameInterface::NewGameData_Implementation(FirstLevel);
	SaveGameRef = Cast<USmashersSaveGame>(UGameplayStatics::CreateSaveGameObject(USmashersSaveGame::StaticClass()));
	SaveGameRef->SetLevelName(FirstLevel);
	UGameplayStatics::OpenLevel(GetWorld(), *FirstLevel);
}

USmashersSaveGame* USmashersGameInstance::GetGameData_Implementation()
{
	return SaveGameRef;
}

void USmashersGameInstance::SaveLevelData_Implementation(FLevelData LevelData)
{
	ISaveGameInterface::SaveLevelData_Implementation(LevelData);
	SaveGameRef->LevelData = LevelData;

	Execute_SaveGameData(this);
}

void USmashersGameInstance::Init()
{
	Super::Init();
	
}

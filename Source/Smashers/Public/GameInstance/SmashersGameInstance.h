// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveData/LevelData.h"
#include "SaveData/SaveGameInterface.h"
#include "SmashersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API USmashersGameInstance : public UGameInstance, public ISaveGameInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	USmashersSaveGame* SaveGameRef;
	UPROPERTY(EditAnywhere)
	FString SlotName = "SmashersSavings";
	UPROPERTY(EditAnywhere)
	FString NoSavingsMenu = "NoStorySavingsMenu";

	virtual void LoadGameData_Implementation() override;
	virtual void SaveGameData_Implementation() override;
	virtual void NewGameData_Implementation(const FString& FirstLevel) override;
	virtual USmashersSaveGame* GetGameData_Implementation() override;
	virtual void SaveLevelData_Implementation(FLevelData LevelData) override;
	virtual void Init() override;
};

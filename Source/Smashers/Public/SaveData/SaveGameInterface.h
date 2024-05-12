// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelData.h"
#include "SmashersSaveGame.h"
#include "UObject/Interface.h"
#include "SaveGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SMASHERS_API ISaveGameInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	void LoadGameData();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	void SaveGameData();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	void NewGameData(const FString& FirstLevel);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	USmashersSaveGame* GetGameData();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	void SaveLevelData(FLevelData LevelData);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interface")
	void SaveCharacterData(FLevelData CharacterData);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};

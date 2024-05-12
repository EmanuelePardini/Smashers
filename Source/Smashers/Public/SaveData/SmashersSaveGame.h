// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelData.h"
#include "GameFramework/SaveGame.h"
#include "SmashersSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API USmashersSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FLevelData LevelData;

	UFUNCTION()
	FORCEINLINE FLevelData GetLevelData(){return LevelData;}
	UFUNCTION()
	FORCEINLINE void SetLevelName(FString LevelName){LevelData.LevelName = LevelName;}
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterRoster.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "SaveData/LevelData.h"
#include "SmashersGameMode.generated.h"

UCLASS(minimalapi)
class ASmashersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASmashersGameMode();
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	FLevelData GetLevelData();
};




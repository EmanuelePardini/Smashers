// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmashersGameMode.h"

#include "Character/SmashersPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GameInstance/CharacterSelectionSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ASmashersGameMode::ASmashersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASmashersGameMode::BeginPlay()
{
	Super::BeginPlay();
}

FLevelData ASmashersGameMode::GetLevelData()
{
	FLevelData LevelData;
	UCharacterSelectionSystem* CharacterSelectionSystem = GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>();
	
	
	LevelData.LevelName = GetWorld()->GetName();
	LevelData.CharacterName = CharacterSelectionSystem->GetSmasher();
	
	return LevelData;
}
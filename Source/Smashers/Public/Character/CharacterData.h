#pragma once

#include "CoreMinimal.h"
#include "Character/SmashersPlayerCharacter.h"
#include "CharacterData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	FString SmasherName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	TSubclassOf<ASmashersPlayerCharacter> Smasher;
};
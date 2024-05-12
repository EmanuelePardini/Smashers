#pragma once
#include "CoreMinimal.h"
#include "Smashers/SmashersGameMode.h"
#include "GameModeData.generated.h"

USTRUCT(BlueprintType)
struct FGameModeData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Setup")
	FString GameModeName;
};
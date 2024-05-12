#pragma once
#include "CoreMinimal.h"
#include "LevelData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FLevelData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;
};

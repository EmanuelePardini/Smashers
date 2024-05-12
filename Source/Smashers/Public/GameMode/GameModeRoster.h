#pragma once

#include "CoreMinimal.h"
#include "GameModeData.h"
#include "Engine/DataAsset.h"
#include "GameModeRoster.generated.h"

UCLASS()
class SMASHERS_API UGameModeRoster : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Setup")
	TArray<FGameModeData> GameModes;
};

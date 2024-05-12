// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "Engine/DataAsset.h"
#include "CharacterRoster.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API UCharacterRoster : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Setup")
	TArray<FCharacterData> Characters;
};

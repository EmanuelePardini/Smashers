// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInputData.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API UPlayerInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FString MappingName;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	class UInputAction* Move;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Jump;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Run;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* LightAttack;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* HeavyAttack;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* LightAttack2;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* HeavyAttack2;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Defend;
};

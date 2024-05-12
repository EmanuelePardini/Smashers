// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CharacterSelectionSystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API UCharacterSelectionSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	FString SmasherName = "Crunch";
	UPROPERTY(VisibleAnywhere)
	FString Smasher2Name = "Yin";
	UPROPERTY(VisibleAnywhere)
	FString LastWinnerSmasher = "";
	UPROPERTY(VisibleAnywhere)
	FString SosiaPrefix = " DoppelGanger";
	
public:
	UFUNCTION(BlueprintCallable)
	FString GetSmasher();
	UFUNCTION(BlueprintCallable)
	FString GetSmasher2();
	UFUNCTION(BlueprintCallable)
	FString SetSmasher(FString SelectedSmasher);
	UFUNCTION(BlueprintCallable)
	FString SetSmasher2(FString SelectedSmasher);
	UFUNCTION(BlueprintCallable)
	FString GetLastWinner();
	UFUNCTION(BlueprintCallable)
	FString SetLastWinner(FString WinnerSmasher);
};

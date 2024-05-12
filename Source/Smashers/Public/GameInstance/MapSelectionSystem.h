// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MapSelectionSystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API UMapSelectionSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	FString MapName;
	
	UFUNCTION(BlueprintCallable)
	FString GetMap();
	UFUNCTION(BlueprintCallable)
	FString SetMap(FString SelectedMap);
};

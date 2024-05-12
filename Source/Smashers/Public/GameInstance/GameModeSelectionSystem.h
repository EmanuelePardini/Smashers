// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameModeSelectionSystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API UGameModeSelectionSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	FString GmName = "Default";
	UPROPERTY(VisibleAnywhere)
	bool Is3dMode = false;

public:
	UFUNCTION(BlueprintCallable)
	FString GetGm();
	UFUNCTION(BlueprintCallable)
	FString SetGm(FString SelectedGm);
	UFUNCTION(BlueprintCallable)
	bool Set3d(bool Selected3d);
	UFUNCTION(BlueprintCallable)
	bool Get3d();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character/CharacterRoster.h"
#include "Character/SmashersPlayerCharacter.h"
#include "SmashersAIController.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API ASmashersAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ASmashersPlayerCharacter* SmasherCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName PlayerStartTag = "Second";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UCharacterRoster* CharacterRoster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float AcceptableRange = 150.f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float DefendDelay = 0.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float DefendTimer = 0.f;

protected:
	virtual void BeginPlay() override;
	ASmashersPlayerCharacter* SpawnPawn();

public:
	virtual void Tick(float DeltaSeconds) override;
	void ManageTimers(float DeltaTime);
	void ManageSmasher();
	bool IsDistanceAcceptable();
	void Move(bool bToEnemy = true);
	void Defend();
	void ManageAttack();
};

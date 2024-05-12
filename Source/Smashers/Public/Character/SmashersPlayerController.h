// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterRoster.h"
#include "InputActionValue.h"
#include "SmashersPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "SmashersPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API ASmashersPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UPlayerInputData* InputData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UInputMappingContext* IMC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName PlayerStartTag = "First";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ASmashersPlayerCharacter* SmasherCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	UCharacterRoster* CharacterRoster;
	

private:
	virtual void BeginPlay() override;

public:
	
	ASmashersPlayerCharacter* SpawnPawn();
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	
	//Primary Actions
	void Move(const FInputActionValue& Value);

	//Jump Manage
	void Jump(const FInputActionValue& Value);

	//Run Manage
	void Run(const FInputActionValue& Value);
	void EndRun(const FInputActionValue& Value);
	

	//Attack Manage
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);
	void LightAttack2(const FInputActionValue& Value);
	void HeavyAttack2(const FInputActionValue& Value);
	void Defend(const FInputActionValue& Value);
	void EndDefend(const FInputActionValue& Value);
};

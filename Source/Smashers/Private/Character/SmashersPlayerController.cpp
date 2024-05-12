// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashersPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/CharacterData.h"
#include "Character/CharacterRoster.h"
#include "Character/PlayerInputData.h"
#include "GameFramework/PlayerStart.h"
#include "GameInstance/CharacterSelectionSystem.h"
#include "Kismet/GameplayStatics.h"

void ASmashersPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Mapping Context
	FTimerHandle TimerHandle;
	float Delay = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}

		SmasherCharacter = SpawnPawn();
		Possess(SmasherCharacter);
	}, Delay, false);
}

ASmashersPlayerCharacter* ASmashersPlayerController::SpawnPawn()
{
	// Get a pointer to the CharacterSelectionSystem
	UCharacterSelectionSystem* CharacterSelectionSystem = GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>();

	// Get the name of the "Smasher" selected from the CharacterSelectionSystem
	FString SelectedSmasher;
	if(UGameplayStatics::GetPlayerControllerID(this) == 0)
	{
		SelectedSmasher = CharacterSelectionSystem->GetSmasher();
		PlayerStartTag = "First";
	}
	else
	{
		SelectedSmasher = CharacterSelectionSystem->GetSmasher2();
		PlayerStartTag = "Second";
	}
	// Iterate through the characters in the roster to find the one corresponding to the selected name
	for (const FCharacterData& CharacterData : CharacterRoster->Characters)
	{
		if (CharacterData.SmasherName == SelectedSmasher)
		{
			TArray<AActor*> PlayerStarts;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
			for(const auto PSActor : PlayerStarts)
			{
				APlayerStart* PlayerStart = Cast<APlayerStart>(PSActor);
				if(PlayerStart->PlayerStartTag == PlayerStartTag)
				{
					return GetWorld()->SpawnActor<ASmashersPlayerCharacter>(CharacterData.Smasher, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
				}
			}
		}
	}
	// Return nullptr if no corresponding Smasher was found
	return nullptr;
}


void ASmashersPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASmashersPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(InputData->Move, ETriggerEvent::Triggered, this, &ASmashersPlayerController::Move);
		
		//Jumping
		EnhancedInputComponent->BindAction(InputData->Jump, ETriggerEvent::Triggered, this, &ASmashersPlayerController::Jump);

		//Running
		EnhancedInputComponent->BindAction(InputData->Run, ETriggerEvent::Triggered, this, &ASmashersPlayerController::Run);
		EnhancedInputComponent->BindAction(InputData->Run, ETriggerEvent::Completed, this, &ASmashersPlayerController::EndRun);
		
		//Attack
		EnhancedInputComponent->BindAction(InputData->LightAttack, ETriggerEvent::Completed, this, &ASmashersPlayerController::LightAttack);
		EnhancedInputComponent->BindAction(InputData->HeavyAttack, ETriggerEvent::Completed, this, &ASmashersPlayerController::HeavyAttack);
		EnhancedInputComponent->BindAction(InputData->LightAttack2, ETriggerEvent::Completed, this, &ASmashersPlayerController::LightAttack2);
		EnhancedInputComponent->BindAction(InputData->HeavyAttack2, ETriggerEvent::Completed, this, &ASmashersPlayerController::HeavyAttack2);
		EnhancedInputComponent->BindAction(InputData->Defend, ETriggerEvent::Started, this, &ASmashersPlayerController::Defend);
		EnhancedInputComponent->BindAction(InputData->Defend, ETriggerEvent::Completed, this, &ASmashersPlayerController::EndDefend);
	}
}

void ASmashersPlayerController::Move(const FInputActionValue& Value)
{
	SmasherCharacter->Move(Value);
}

void ASmashersPlayerController::Jump(const FInputActionValue& Value)
{
	SmasherCharacter->Jump();
}

void ASmashersPlayerController::Run(const FInputActionValue& Value)
{
	SmasherCharacter->Run(Value);
}

void ASmashersPlayerController::EndRun(const FInputActionValue& Value)
{
	SmasherCharacter->EndRun(Value);
}

void ASmashersPlayerController::LightAttack(const FInputActionValue& Value)
{
	SmasherCharacter->LightAttack(Value);
}

void ASmashersPlayerController::HeavyAttack(const FInputActionValue& Value)
{
	SmasherCharacter->HeavyAttack(Value);
}

void ASmashersPlayerController::LightAttack2(const FInputActionValue& Value)
{
	SmasherCharacter->LightAttack2(Value);
}

void ASmashersPlayerController::HeavyAttack2(const FInputActionValue& Value)
{
	SmasherCharacter->HeavyAttack2(Value);
}

void ASmashersPlayerController::Defend(const FInputActionValue& Value)
{
	SmasherCharacter->Defend(Value);
}

void ASmashersPlayerController::EndDefend(const FInputActionValue& Value)
{
	SmasherCharacter->EndDefend(Value);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SmashersAIController.h"

#include "GameFramework/PlayerStart.h"
#include "GameInstance/CharacterSelectionSystem.h"
#include "Kismet/GameplayStatics.h"

void ASmashersAIController::BeginPlay()
{
	Super::BeginPlay();
	SmasherCharacter = SpawnPawn();
	Possess(SmasherCharacter);
}


ASmashersPlayerCharacter* ASmashersAIController::SpawnPawn()
{
	// Get a pointer to the CharacterSelectionSystem
	UCharacterSelectionSystem* CharacterSelectionSystem = GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>();

	// Get the name of the "Smasher" selected from the CharacterSelectionSystem
	FString SelectedSmasher = CharacterSelectionSystem->GetSmasher2();
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

void ASmashersAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ManageSmasher();
	ManageTimers(DeltaSeconds);
}

void ASmashersAIController::ManageTimers(float DeltaTime)
{
	if(SmasherCharacter->GetIsDefending())
		DefendTimer += DeltaTime;
	if(DefendTimer >= DefendDelay)
	{
		DefendTimer = 0.f;
		SmasherCharacter->EndDefend(true);
	}
}

void ASmashersAIController::ManageSmasher()
{
	if(SmasherCharacter && !SmasherCharacter->GetIsDead())
	{
		if(!IsDistanceAcceptable())
		{
			Move(true);
		}
		else
		{
			if(!SmasherCharacter->GetIsHitReacting())
			{
				ManageAttack();
			}
			else
			{
				Defend();
			}
		}
	}
}

bool ASmashersAIController::IsDistanceAcceptable()
{
	if(!SmasherCharacter->Enemy) return false;
	
	// Calculate the distance between the Smasher character and the enemy
	float DistanceToEnemy = FVector::Distance(SmasherCharacter->Enemy->GetActorLocation(), SmasherCharacter->GetActorLocation());

	// Check if the enemy is within the acceptable range
	return DistanceToEnemy <= AcceptableRange;
}

void ASmashersAIController::Move(bool bToEnemy)
{
	if (SmasherCharacter && SmasherCharacter->Enemy)
	{
		// Get the position of the Smasher character
		FVector SmasherPosition = SmasherCharacter->GetActorLocation();

		// Get the position of the enemy
		FVector EnemyPosition = SmasherCharacter->Enemy->GetActorLocation();

		// Calculate the direction vector towards the enemy
		FVector MoveDirection = (EnemyPosition - SmasherPosition).GetSafeNormal();

		// Convert the direction vector into a 2D movement input
		FVector2d MovementInput;
		if(bToEnemy)
		{
			MovementInput = FVector2d(MoveDirection.Y, MoveDirection.X); // Swap Y and X for UE4 coordinate system
		}
		else
		{
			MovementInput = FVector2d(MoveDirection.Y, -MoveDirection.X);
		}

		// Move the Smasher character towards the enemy
		SmasherCharacter->Move(MovementInput);

		//Probability of Jump
		float ActionProb = FMath::RandRange(1,50);
		if(ActionProb == 50) SmasherCharacter->Jump();

		//Probability of Run
		ActionProb = FMath::RandRange(1,20);
		if(ActionProb == 20) SmasherCharacter->Run(true);
	}
}

void ASmashersAIController::Defend()
{
	float DefendProb = FMath::RandRange(1,5);
	if(!SmasherCharacter->GetIsDefending() && DefendProb == 5)
	{
		SmasherCharacter->Defend(true);
		DefendDelay = FMath::RandRange(1,4);
	}
}

void ASmashersAIController::ManageAttack()
{
	int RandAttack = FMath::RandRange(0,3);
	switch (RandAttack)
	{
	case 0:
		SmasherCharacter->LightAttack(true);
		break;
	case 1:
		SmasherCharacter->LightAttack2(true);
		break;
	case 2:
		SmasherCharacter->HeavyAttack(true);
		break;
	case 3:
		SmasherCharacter->HeavyAttack2(true);
		break;
	default:
		break;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttackComponent.h"

#include "Character/SmashersPlayerCharacter.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	BuildHitBoxArray();
}

void UAttackComponent::BuildHitBoxArray()
{
	TArray<UHitBoxPieceComponent*> AllHitBoxes;
	GetOwner()->GetComponents<UHitBoxPieceComponent>(AllHitBoxes);
	
	for (UHitBoxPieceComponent* HitBox : AllHitBoxes)
	{
		if (HitBox->IsAttackHitBox)
		{
			AttackHitBoxes.Add(HitBox);
		}
	}
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageComboTime(DeltaTime);
}

bool UAttackComponent::Attack(bool IsLightAttack)
{
	bool Success = false;
	
	if(!GetOwner()) return false;
	
	for (auto AttackHitBox : AttackHitBoxes)
	{
		UWorld* Context = GetWorld();
		AActor* Owner = GetOwner();
		FVector Start = AttackHitBox->GetComponentLocation();
		FVector End = Start + Owner->GetActorForwardVector() * Distance;
		TArray<FHitResult> Hits;
		SphereRadius = AttackHitBox->GetScaledSphereRadius();

		// Draw a debug sphere to visualize the sphere trace
		//DrawDebugSphere(Context, Start, SphereRadius, 12, FColor::Red, false, 2.f);

		// Perform a sphere trace against objects with the specified collision profile
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Owner);
		Context->SweepMultiByProfile(Hits, Start, End, FQuat::Identity, InteractionMask, FCollisionShape::MakeSphere(SphereRadius), Params);

		// Iterate through each hit result
		for (auto Hit : Hits)
		{
			// Get info of the hit
			AActor* HittedActor = Hit.GetActor();
			ASmashersPlayerCharacter* Enemy = Cast<ASmashersPlayerCharacter>(HittedActor);
			UActorComponent* HittedComponent = Hit.GetComponent();
			UHitBoxPieceComponent* EnemyHitBox = Cast<UHitBoxPieceComponent>(HittedComponent);

			if (Enemy && EnemyHitBox)
			{
				// Calculate Damage
				float FinalDamage = IsLightAttack ?
					EnemyHitBox->AdaptDamage(LightAttackDamage + (Combo * 0.1)):
					EnemyHitBox->AdaptDamage(HeavyAttackDamage + (Combo * 0.2));
				

				// Calculate if enemy is defending
				FinalDamage = Enemy->GetIsDefending() ? FinalDamage * 0.1f : FinalDamage;

				// Apply the calculated Damage
				Enemy->HealthComponent->DecrementHealth(FinalDamage);
				
				FVector ImpulseDirection = (Enemy->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal(); // Get forward direction
				
				// Calculate the impulse force to be applied
				FVector ImpulseForce = ImpulseDirection * ImpulseStrength;
				if(!IsLightAttack) Enemy->LaunchCharacter(ImpulseForce,false,false);
				Success = true;
				break; // Exit the loop after handling the first valid hit
			}
		}
		if (Success) break;
	}
	Success ? IncrementCombo(ComboIncrementAmount) : ResetCombo();
	return Success;
}

void UAttackComponent::IncrementCombo(int Amount)
{
	Combo += Amount;
	if(Combo > MaxCombo) MaxCombo = Combo;
	OnCombo.Broadcast();
}

void UAttackComponent::ResetCombo()
{
	Combo = 0;
	ComboTimer = 0;
	OnCombo.Broadcast();
}

void UAttackComponent::ManageComboTime(float DeltaTime)
{
	//if(Combo>0) GEngine->AddOnScreenDebugMessage(-1,5, FColor::Green,FString::Printf(TEXT("%d"), Combo));
	ComboTimer += DeltaTime;

	if(ComboTimer >= ComboDelay)
	{
		ResetCombo();
	}
}





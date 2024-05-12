// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BuildHitBoxArray();
	ActualHealth = MaxHealth;
}

void UHealthComponent::BuildHitBoxArray()
{
	GetOwner()->GetComponents<UHitBoxPieceComponent>(HitBoxes);

	// for (auto HitBox : HitBoxes)
	// {
	// 	HitBox->SetHiddenInGame(false);
	// }
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DecrementHealth(int DamageAmount)
{
	if(bIsDead) return;
	
	OnHealthDecrement.Broadcast();
	
	ActualHealth -= DamageAmount;

	if(ActualHealth <= 0)
	{
		ActualHealth = 0;
		Die();
	}
}

void UHealthComponent::IncrementHealth(int IncrementAmount)
{
	ActualHealth += IncrementAmount;

	if(ActualHealth > MaxHealth)
	{
		ActualHealth = MaxHealth;
	}
}

void UHealthComponent::Die()
{
	OnDie.Broadcast();
	bIsDead = true;
}


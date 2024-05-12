// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HitBoxPieceComponent.h"

// Sets default values for this component's properties
UHitBoxPieceComponent::UHitBoxPieceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHitBoxPieceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitBoxPieceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHitBoxPieceComponent::AdaptDamage(float OriginalDamage)
{
	float NewDamage = OriginalDamage * DamageMultiplier;
	
	return NewDamage;
}


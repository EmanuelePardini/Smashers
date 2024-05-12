// Fill out your copyright notice in the Description page of Project Settings.


#include "Miscellaneous/Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnDelay = FMath::RandRange(SpawnDelayMin,SpawnDelayMax);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageSpawnDelay(DeltaTime);
}

void ASpawner::ManageSpawnDelay(float DeltaTime)
{
	// Increment the timer
	SpawnTimer += DeltaTime;

	// Check if it's time to spawn
	if (SpawnTimer >= SpawnDelay)
	{
		Spawn();
		SpawnTimer = 0.0f;
		SpawnDelay = FMath::RandRange(SpawnDelayMin,SpawnDelayMax);
	}
}

void ASpawner::Spawn()
{
	int SpawnableIndex = FMath::RandRange(0,Spawnables.Num()-1);
	
	if (!Spawnables[SpawnableIndex] || !SpawnBox) return;
	
	// Get a random location within the spawn box
	FVector SpawnLocation = FMath::RandPointInBox(SpawnBox->GetComponentsBoundingBox());

	// Spawn the actor at the random location
	GetWorld()->SpawnActor<AActor>(Spawnables[SpawnableIndex], SpawnLocation, FRotator::ZeroRotator);
}


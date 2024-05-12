// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class SMASHERS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelayMin = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelayMax = 40.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpawnTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> Spawnables;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATriggerBox* SpawnBox;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ManageSpawnDelay(float DeltaTime);
	void Spawn();
};

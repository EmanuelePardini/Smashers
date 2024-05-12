// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "HitBoxPieceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMASHERS_API UHitBoxPieceComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitBoxPieceComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Setup")
	FName HitBoxTag = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float DamageMultiplier = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	bool IsAttackHitBox = false;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float AdaptDamage(float OriginalDamage);
};

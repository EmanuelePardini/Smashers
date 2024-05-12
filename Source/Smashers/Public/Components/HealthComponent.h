// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitBoxPieceComponent.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMASHERS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float MaxHealth = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float ActualHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UHitBoxPieceComponent*> HitBoxes;

	//Delegates for Health Changes
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
	FOnDie OnDie;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	bool bIsDead = false;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDecrement);
	FOnHealthDecrement OnHealthDecrement;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void BuildHitBoxArray();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void DecrementHealth(int DamageAmount);
	UFUNCTION(BlueprintCallable)
	void IncrementHealth(int IncrementAmount);
	UFUNCTION(BlueprintCallable)
	void Die();
		
};

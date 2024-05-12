// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitBoxPieceComponent.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMASHERS_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float LightAttackDamage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float HeavyAttackDamage = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	FName InteractionMask = "OverlapAllDynamic";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float Distance = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float ImpulseStrength = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float SphereRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UHitBoxPieceComponent*> AttackHitBoxes;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombo);
	FOnCombo OnCombo;

protected:
	//Combo Manage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Combo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxCombo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ComboIncrementAmount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timer")
	float ComboDelay = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ComboTimer = 0.f;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void BuildHitBoxArray();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Attack(bool IsLightAttack);
	UFUNCTION()
	void IncrementCombo(int Amount);
	UFUNCTION()
	void ResetCombo();
	UFUNCTION()
	void ManageComboTime(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCombo(){return Combo;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxCombo(){return MaxCombo;}
};

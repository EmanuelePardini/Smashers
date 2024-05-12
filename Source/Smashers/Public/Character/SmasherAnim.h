// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SmasherAnim.generated.h"

/**
 * 
 */
UCLASS()
class SMASHERS_API USmasherAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	//All public variables are setted in the Character Input settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsHeavyAttack1 = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsHeavyAttack2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsLightAttack1 = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsLightAttack2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDefending = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsHitReacting = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDead = false;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsGrounded = true;



public:
	void Animate(ACharacter* Character, FVector LookDirection = FVector(0,0,0));
	
	FVector GetDeltaRoot(){return ConsumeExtractedRootMotion(1).GetRootMotionTransform().GetLocation();}
};

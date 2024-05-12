// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/AttackComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "SaveData/LevelData.h"
#include "SmashersPlayerCharacter.generated.h"

UCLASS()
class SMASHERS_API ASmashersPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASmashersPlayerCharacter();

	//Enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASmashersPlayerCharacter* Enemy;

	//Camera
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LookDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector StartLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Is3dChar;

	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UAttackComponent* AttackComponent;

protected:
	//Movement Property
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float WalkSpeed = 200.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float RunSpeed = 300.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float JumpSpeed = 700.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float LightAttackSpeed = 0.4f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float HeavyAttackSpeed = 0.8f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	float HitReactSpeed = 0.6f;

	//Others Properties
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	FString TagName = "";

	
	//Animations
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USmasherAnim* Animations;

	//Actions State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="State")
	bool CanMove = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="State")
	bool IsHitReacting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="State")
	bool IsAttacking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="State")
	bool IsDefending = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="State")
	bool IsDead = false;


	//Manage Timers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	float LightAttack1Timer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	float LightAttack2Timer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	float HeavyAttack1Timer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	float HeavyAttack2Timer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Timer")
	float ComboTimer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	bool CanLightAttack1 = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	bool CanLightAttack2 = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	bool CanHeavyAttack1 = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Timer")
	bool CanHeavyAttack2 = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Primary Actions
	void Move(const FInputActionValue& Value);
	void ManageLook(ASmashersPlayerCharacter* Objective);
	void ManageCamera(ASmashersPlayerCharacter* OtherCharacter);

	//Run Manage
	void Run(const FInputActionValue& Value);
	void EndRun(const FInputActionValue& Value);
	
	//Attack Manage
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LightAttack(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HeavyAttack(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LightAttack2(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HeavyAttack2(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Defend(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) 
	void EndDefend(const FInputActionValue& Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HitReact();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) 
	void Die();

	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayLightAttack();
	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayHeavyAttack();
	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayLightAttack2();
	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayHeavyAttack2();
	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayDefend();
	UFUNCTION(BlueprintImplementableEvent) //for audio and VFX
	void PlayEndDefend();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitReact();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDie();

	UFUNCTION()
	void ManageCombatTimers(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void UpdateMovementParams(float NewWalkSpeed = 0, float NewRunSpeed = 0, float NewJumpSpeed = 0);
	UFUNCTION()
	ASmashersPlayerCharacter* RelevateEnemy();

	//Getters
	UFUNCTION()
	FORCEINLINE bool GetIsDefending(){return IsDefending;}
	UFUNCTION()
	FORCEINLINE bool GetIsHitReacting(){return IsHitReacting;}
	UFUNCTION()
	FORCEINLINE bool GetIsDead(){return IsDead;}
	
	//Data
	UFUNCTION(BlueprintCallable)
	FLevelData GetLevelData();

};

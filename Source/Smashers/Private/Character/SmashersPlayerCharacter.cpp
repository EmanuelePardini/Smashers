// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashersPlayerCharacter.h"

#include "AI/SmashersAIController.h"
#include "Character/SmasherAnim.h"
#include "Character/SmashersPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance/CharacterSelectionSystem.h"
#include "GameInstance/GameModeSelectionSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASmashersPlayerCharacter::ASmashersPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(RootComponent);

	//Movement Settings
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	//Components Settings
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDie.AddDynamic(this, &ASmashersPlayerCharacter::Die);
	HealthComponent->OnHealthDecrement.AddDynamic(this, &ASmashersPlayerCharacter::HitReact);

	AttackComponent = CreateDefaultSubobject<UAttackComponent>("AttackComponent");
}

// Called when the game starts or when spawned
void ASmashersPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle RelevateEnemyTimer;
	GetWorldTimerManager().SetTimer(RelevateEnemyTimer, [this]()
		{
			Enemy = RelevateEnemy();
		}, 0.25f, false);
	
	Animations = Cast<USmasherAnim>(GetMesh()->GetAnimInstance());
	StartLocation = GetActorLocation();
	Is3dChar = GetGameInstance()->GetSubsystem<UGameModeSelectionSystem>()->Get3d();
}

// Called every frame
void ASmashersPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Animations) Animations->Animate(this, LookDirection);
	if(Enemy) ManageLook(Enemy);
	if(Enemy) ManageCamera(Enemy);
	ManageCombatTimers(DeltaTime);
}

void ASmashersPlayerCharacter::Move(const FInputActionValue& Value)
{
	if(!CanMove || IsDead) return;
	
	// Obtains the controller's rotation and create a rotation on the yaw axis
	FVector2d MovementValue = Value.Get<FVector2d>();
	
	// Adds movement input along the forward axis (ForwardDirection) and the right axis (RightDirection)

		AddMovementInput(LookDirection.GetAbs(), MovementValue.Y);
		AddMovementInput(LookDirection.GetAbs(), MovementValue.X);
}

void ASmashersPlayerCharacter::ManageLook(ASmashersPlayerCharacter* Objective)
{
	FVector ObjectiveLoc = Objective->GetActorLocation();
	LookDirection = (ObjectiveLoc - GetActorLocation()).GetSafeNormal();
	ObjectiveLoc.Z = 0.f;
	LookDirection.Z= 0.f;
    FQuat LookAtRotation = FQuat::FindBetweenVectors(FVector::RightVector, LookDirection);
	FRotator FinalRotation = FRotator(GetActorRotation().Pitch, LookAtRotation.Rotator().Yaw, GetActorRotation().Roll);
	
    GetMesh()->SetWorldRotation(FinalRotation);
}

void ASmashersPlayerCharacter::ManageCamera(ASmashersPlayerCharacter* OtherCharacter)
{
	FVector CameraLocation = (GetActorLocation() + OtherCharacter->GetActorLocation()) / 2.f;
	
	FVector CharacterForward = GetActorForwardVector();
	bool bCharacterForwardX = FMath::Abs(CharacterForward.X) > FMath::Abs(CharacterForward.Y);
	
	if (bCharacterForwardX)
	{
		if(!Is3dChar) SetActorLocation(FVector(GetActorLocation().X,StartLocation.Y, GetActorLocation().Z));
		CameraLocation.Y = CameraComponent->GetComponentLocation().Y;
	}
	else
	{
		if(!Is3dChar) SetActorLocation(FVector(StartLocation.X,GetActorLocation().Y, GetActorLocation().Z));
		CameraLocation.X = CameraComponent->GetComponentLocation().X;
	}
	
	CameraComponent->SetWorldLocation(CameraLocation);
}

void ASmashersPlayerCharacter::Run(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ASmashersPlayerCharacter::EndRun(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASmashersPlayerCharacter::LightAttack_Implementation(const FInputActionValue& Value)
{
	if(CanLightAttack1 && !IsDefending && !IsAttacking && !IsDead)
	{
		CanLightAttack1 = false;
			
		//Animations
		if(Animations) Animations->IsLightAttack1 = true;
		IsAttacking = true;
		CanMove = false;
		
		//For attack component execution it will be called in the middle of the attack timer
		FTimerHandle AttackHandle;
		GetWorldTimerManager().SetTimer(AttackHandle, [this]()
		{
			//AttackComp
			bool bAttackSuccess = AttackComponent->Attack(true);
			//VFX and Audio in BP
			if(bAttackSuccess) PlayLightAttack();
		}, LightAttackSpeed / 2, false);

		//At the end of the attack
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if(Animations) Animations->IsLightAttack1 = false;
			IsAttacking = false;
			if(!IsDefending) CanMove = true;
		}, LightAttackSpeed, false);
		

	}
}

void ASmashersPlayerCharacter::HeavyAttack_Implementation(const FInputActionValue& Value)
{
	if(CanHeavyAttack1 && !IsDefending && !IsAttacking && !IsDead)
	{
		CanHeavyAttack1 = false;
		
		//Animations
		if(Animations) Animations->IsHeavyAttack1 = true;
		IsAttacking = true;
		CanMove = false;

		//For attack component execution it will be called in the middle of the attack timer
		FTimerHandle AttackHandle;
		GetWorldTimerManager().SetTimer(AttackHandle, [this]()
		{
			//AttackComp
			bool bAttackSuccess = AttackComponent->Attack(false);
			//VFX and Audio in BP
			if(bAttackSuccess) PlayHeavyAttack();
		}, HeavyAttackSpeed / 2, false);

		//At the end of the attack
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if(Animations) Animations->IsHeavyAttack1 = false;
			IsAttacking = false;
			if(!IsDefending) CanMove = true;
		}, HeavyAttackSpeed, false);


	}
}

void ASmashersPlayerCharacter::LightAttack2_Implementation(const FInputActionValue& Value)
{
	if(CanLightAttack2 && !IsDefending && !IsAttacking && !IsDead)
	{
		CanLightAttack2 = false;
		
		//Animations
		if(Animations) Animations->IsLightAttack2 = true;
		IsAttacking = true;
		CanMove = false;

		//For attack component execution it will be called in the middle of the attack timer
		FTimerHandle AttackHandle;
		GetWorldTimerManager().SetTimer(AttackHandle, [this]()
		{
			//AttackComp
			bool bAttackSuccess = AttackComponent->Attack(true);
			//VFX and Audio in BP
			if(bAttackSuccess) PlayLightAttack2();
		}, LightAttackSpeed / 2, false);

		//At the end of the attack
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if(Animations) Animations->IsLightAttack2 = false;
			IsAttacking = false;
			if(!IsDefending) CanMove = true;
		}, LightAttackSpeed, false);


	}
}

void ASmashersPlayerCharacter::HeavyAttack2_Implementation(const FInputActionValue& Value)
{
	if(CanHeavyAttack2 && !IsDefending && !IsAttacking && !IsDead)
	{
		CanHeavyAttack2 = false;
		
		//Animations
		if(Animations) Animations->IsHeavyAttack2 = true;
		IsAttacking = true;
		CanMove = false;

		//For attack component execution it will be called in the middle of the attack timer
		FTimerHandle AttackHandle;
		GetWorldTimerManager().SetTimer(AttackHandle, [this]()
		{
			//AttackComp
			bool bAttackSuccess = AttackComponent->Attack(false);
			//VFX and Audio in BP
			if(bAttackSuccess) PlayHeavyAttack2();
		}, HeavyAttackSpeed / 2, false);

		//At the end of the attack
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if(Animations) Animations->IsHeavyAttack2 = false;
			IsAttacking = false;
			if(!IsDefending) CanMove = true;
		}, HeavyAttackSpeed, false);


	}
}

void ASmashersPlayerCharacter::Defend_Implementation(const FInputActionValue& Value)
{
	if(IsAttacking) return;
	
	//Animations
	if(Animations) Animations->IsDefending = true;
	IsDefending = true;
	IsAttacking = false;
	CanMove = false;
	
	//VFX and Audio in BP
	PlayDefend();
}

void ASmashersPlayerCharacter::EndDefend_Implementation(const FInputActionValue& Value)
{
	if(Animations) Animations->IsDefending = false;
	IsDefending = false;
	CanMove = true;
	
	//VFX and Audio in BP
	PlayEndDefend();
}

void ASmashersPlayerCharacter::HitReact_Implementation()
{
	//Animations
	if(Animations) Animations->IsHitReacting = true;
	IsHitReacting = true;
	CanMove = false;
	IsAttacking = false;
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	{
		if(Animations) Animations->IsHitReacting = false;
		IsHitReacting = false;
		if(!IsDefending) CanMove = true;
	}, HitReactSpeed, false);
	
	//VFX and Audio in BP
	PlayHitReact();
}


void ASmashersPlayerCharacter::Die_Implementation()
{
	UCharacterSelectionSystem* CharacterSelectionSystem = GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>();
	if(Animations) Animations->IsDead = true;
	IsDead = true;
	CanMove = false;
	IsDefending = false;
	
	//Save last winner
	if(TagName == CharacterSelectionSystem->GetSmasher())
	{
		GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>()->SetLastWinner(CharacterSelectionSystem->GetSmasher2());
	}
	else
	{
		GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>()->SetLastWinner(CharacterSelectionSystem->GetSmasher());
	}

	//VFX and Audio in BP
	PlayDie();
}

void ASmashersPlayerCharacter::ManageCombatTimers(float DeltaTime)
{
	if(!CanLightAttack1)
	{
		LightAttack1Timer += DeltaTime;
		if(LightAttack1Timer >= LightAttackSpeed)
		{
			CanLightAttack1 = true;
			LightAttack1Timer = 0.f;
		}
	}

	if(!CanLightAttack2)
	{
		LightAttack2Timer += DeltaTime;
		if(LightAttack2Timer >= LightAttackSpeed)
		{
			CanLightAttack2 = true;
			LightAttack2Timer = 0.f;
		}
	}

	if(!CanHeavyAttack1)
	{
		HeavyAttack1Timer += DeltaTime;
		if(HeavyAttack1Timer >= HeavyAttackSpeed)
		{
			CanHeavyAttack1 = true;
			HeavyAttack1Timer = 0.f;
		}
	}

	if(!CanHeavyAttack2)
	{
		HeavyAttack2Timer += DeltaTime;
		if(HeavyAttack2Timer >= HeavyAttackSpeed)
		{
			CanHeavyAttack2 = true;
			HeavyAttack2Timer = 0.f;
		}
	}
}

void ASmashersPlayerCharacter::UpdateMovementParams(float NewWalkSpeed, float NewRunSpeed, float NewJumpSpeed)
{
	if(NewWalkSpeed > 0) WalkSpeed = NewWalkSpeed;
	if(NewRunSpeed > 0) RunSpeed = NewRunSpeed;
	if(NewJumpSpeed > 0) JumpSpeed = NewJumpSpeed;

	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

ASmashersPlayerCharacter* ASmashersPlayerCharacter::RelevateEnemy()
{
	TArray<AActor*> SmashersCharacters;
	ASmashersPlayerCharacter* Objective = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASmashersPlayerCharacter::StaticClass(), SmashersCharacters);
	
	for(const auto Smasher : SmashersCharacters)
	{
		if(Smasher && Smasher != this ) Objective = Cast<ASmashersPlayerCharacter>(Smasher);
	}

	return Objective;
}

FLevelData ASmashersPlayerCharacter::GetLevelData()
{
	FLevelData LevelData;
	UCharacterSelectionSystem* CharacterSelectionSystem = GetGameInstance()->GetSubsystem<UCharacterSelectionSystem>();
	
	LevelData.LevelName = GetWorld()->GetName();
	LevelData.CharacterName = CharacterSelectionSystem->GetSmasher();
	
	return LevelData;
}

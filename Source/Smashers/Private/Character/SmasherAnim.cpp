// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmasherAnim.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USmasherAnim::Animate(ACharacter* Character, FVector LookDirection)
{
	// Ottieni la velocità assoluta del personaggio
	FVector Velocity = Character->GetCharacterMovement()->Velocity.GetAbs();

	// Aggiorna i parametri in base al movimento del personaggio
	IsGrounded = !Character->GetCharacterMovement()->IsFalling();
	SpeedX = Velocity.X;
	SpeedY = Velocity.Y;

	// Calcola la direzione di movimento
	FVector MovementDirection = Character->GetCharacterMovement()->Velocity.GetSafeNormal();

	// Calcola il vettore di avanti del personaggio
	FVector CharacterForward = Character->GetActorForwardVector();

	// Calcola il prodotto scalare tra il vettore di avanti del personaggio e la direzione di movimento
	float DotProduct = FVector::DotProduct(CharacterForward, MovementDirection);

	// Calcola il prodotto scalare tra il vettore di avanti del personaggio e la direzione in cui guarda
	float LookDotProduct = FVector::DotProduct(CharacterForward, LookDirection);
	
	//Assign Direction
	if(DotProduct <= 0 && LookDotProduct <= 0)
	{
		Direction = 1.f;
	}
	else if(DotProduct > 0 && LookDotProduct <= 0)
	{
		Direction = -1.f;
	}
	else if(DotProduct <= 0 && LookDotProduct > 0)
	{
		Direction = -1.f;
	}
	else if(DotProduct > 0 && LookDotProduct > 0)
	{
		Direction = 1.f;
	}
}

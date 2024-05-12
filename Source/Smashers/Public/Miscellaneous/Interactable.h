// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SmashersPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class SMASHERS_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractDuration = 10.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(ASmashersPlayerCharacter* SmashersPlayerCharacter);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndInteract(ASmashersPlayerCharacter* SmashersPlayerCharacter);
};

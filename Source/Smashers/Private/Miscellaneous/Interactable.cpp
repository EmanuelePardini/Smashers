// Fill out your copyright notice in the Description page of Project Settings.


#include "Miscellaneous/Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASmashersPlayerCharacter* PlayerCharacter = Cast<ASmashersPlayerCharacter>(OtherActor);
	if(PlayerCharacter)
	{
		Interact(PlayerCharacter);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}



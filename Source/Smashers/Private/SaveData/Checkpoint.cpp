// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveData/Checkpoint.h"

#include "Character/SmashersPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "SaveData/SaveGameInterface.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASmashersPlayerCharacter* Player = Cast<ASmashersPlayerCharacter>(OtherActor);
	{
		if(GetGameInstance()->Implements<USaveGameInterface>())
		{
			ISaveGameInterface::Execute_SaveLevelData(GetGameInstance(), Player->GetLevelData());
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, Player->GetLevelData().LevelName);
		}
	}
}

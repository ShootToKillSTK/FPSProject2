// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Start the spawning timer
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy, SpawnInterval, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnEnemy()
{
    if (EnemyClass)
    {
        // Get the base spawn location
        FVector BaseSpawnLocation = GetActorLocation();

        // Generate a random point in a circle and convert it to FVector
        FVector RandomOffset = FVector(FMath::RandPointInCircle(500.0f), 0.0f);

        // Apply the offset to the base location
        FVector SpawnLocation = BaseSpawnLocation + RandomOffset;

        FRotator SpawnRotation = FRotator::ZeroRotator;

        // Spawn the enemy
        AEnemyAICharacter* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyAICharacter>(EnemyClass, SpawnLocation, SpawnRotation);

        if (SpawnedEnemy)
        {
            UE_LOG(LogTemp, Warning, TEXT("Spawned an enemy at location: %s"), *SpawnLocation.ToString());
        }
    }
}


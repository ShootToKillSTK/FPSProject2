// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlowFloor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" 

// Sets default values
ASlowFloor::ASlowFloor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure the Box Component
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetBoxExtent(FVector(400.f, 400.f, 50.f)); // Set size as needed
    BoxComponent->SetCollisionProfileName(TEXT("Trigger")); // Set collision profile
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlowFloor::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASlowFloor::OnOverlapEnd);

    // Create and configure the Static Mesh Component for the floor
    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
    FloorMesh->SetupAttachment(RootComponent); // Attach to RootComponent
    FloorMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // Position the floor below the trigger

    // Set default speed reduction factor
    SpeedReductionFactor = 0.5f; // 50% reduction
    bIsCharacterOnFloor = false; // Initialize boolean
}

// Called when the game starts or when spawned
void ASlowFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlowFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlowFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // Check if the overlapping actor is of type AFPSCharacter
        AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
        if (Character)
        {
            bIsCharacterOnFloor = true;
            // Reduce speed of the character
            Character->GetCharacterMovement()->MaxWalkSpeed *= SpeedReductionFactor;
        }
    }
}

void ASlowFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this)
    {
        AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
        if (Character)
        {
            bIsCharacterOnFloor = false;
            // Restore speed of the character
            Character->GetCharacterMovement()->MaxWalkSpeed /= SpeedReductionFactor;
        }
    }
}


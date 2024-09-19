// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DamagingFloor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADamagingFloor::ADamagingFloor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure the Box Component
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetBoxExtent(FVector(200.f, 200.f, 50.f)); // Set size as needed
    BoxComponent->SetCollisionProfileName(TEXT("Trigger")); // Set collision profile
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamagingFloor::OnOverlapBegin);

    // Create and configure the Static Mesh Component for the floor
    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
    FloorMesh->SetupAttachment(RootComponent); // Attach to RootComponent
    FloorMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // Position the floor below the trigger
    //FloorMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("PathOfMesh"))); // Load your mesh

    // Set default damage amount
    DamageAmount = 5.f;
    bIsCharacterOnFloor = false; // Initialize boolean
}

// Called when the game starts or when spawned
void ADamagingFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamagingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // If the character is on the floor, apply damage
    if (bIsCharacterOnFloor)
    {
        // Ensure the timer is running
        if (!GetWorldTimerManager().IsTimerActive(DamageTimerHandle))
        {
            GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ADamagingFloor::ApplyDamage, 1.0f, true);
        }
    }
}

void ADamagingFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // Check if the overlapping actor is of type AFPSCharacter
        AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
        if (Character)
        {
            bIsCharacterOnFloor = true;
            // Ensure the timer is started
            if (!GetWorldTimerManager().IsTimerActive(DamageTimerHandle))
            {
                GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ADamagingFloor::ApplyDamage, 1.0f, true);
            }
        }
    }
}

void ADamagingFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this)
    {
        AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
        if (Character)
        {
            bIsCharacterOnFloor = false;
            // Stop the timer when the character leaves the floor
            GetWorldTimerManager().ClearTimer(DamageTimerHandle);
        }
    }
}

void ADamagingFloor::ApplyDamage()
{
    // Apply damage to all characters currently on the floor
    TArray<AActor*> OverlappingActors;
    BoxComponent->GetOverlappingActors(OverlappingActors, AFPSCharacter::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        AFPSCharacter* Character = Cast<AFPSCharacter>(Actor);
        if (Character)
        {
            // Apply damage to the character
            TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
            FDamageEvent DamageEvent(DamageType);
            Character->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
        }
    }
}


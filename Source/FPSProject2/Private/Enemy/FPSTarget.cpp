// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FPSTarget.h"

// Sets default values
AFPSTarget::AFPSTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
}

// Called when the game starts or when spawned
void AFPSTarget::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AFPSTarget::HitMesh);
}

// Called every frame
void AFPSTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSTarget::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if OtherActor is of type FPSProjectile
	if (OtherActor->IsA(AFPSProjectile::StaticClass()))
	{
		// Update HUD with points
		AMyHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AMyHUD>();
		if (HUD)
		{
			HUD->gameWidgetContainer->SetScoreText(Points);
		}

		// Log and destroy both the enemy and the projectile
		UE_LOG(LogTemp, Warning, TEXT("Hit detected with: %s"), *OtherActor->GetName());

		// Destroy the enemy character
		Destroy();

		// Destroy the projectile (OtherActor)
		OtherActor->Destroy();
	}
}


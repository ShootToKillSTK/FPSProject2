// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAICharacter.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Capsule Component
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));

	// Attach the capsule to the root component (or skeletal mesh)
	CollisionCapsule->SetupAttachment(RootComponent);  // You can also attach it to the Mesh if needed

	// Set the capsule size (height and radius)
	CollisionCapsule->InitCapsuleSize(42.f, 96.f); // You can adjust this size
	//CollisionCapsule->SetNotifyRigidBodyCollision(true);

	// Bind the OnHit function
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AEnemyAICharacter::HitCharacter);

	//USkeletalMeshComponent* CharacterMesh = GetMesh();
	//if (CharacterMesh)
	//{
	//	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//	CharacterMesh->SetCollisionObjectType(ECC_Pawn);
	//	CharacterMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//	CharacterMesh->SetNotifyRigidBodyCollision(true);

	//	// Bind hit event
	//	CharacterMesh->OnComponentHit.AddDynamic(this, &AEnemyAICharacter::HitCharacter);
	//}
}

void AEnemyAICharacter::HitCharacter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

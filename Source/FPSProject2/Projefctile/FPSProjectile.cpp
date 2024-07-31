// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the Sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set Projectile specific collisions we made in Project settings -> Collisions
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Bind Collision to it (For impulsing see then destroying function)
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnWhateverYouWantToNameIT);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent) {
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = BulletSpeed;
		ProjectileMovementComponent->MaxSpeed = BulletSpeed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent) {
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		// Find the asset
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMesh(TEXT("/Game/Meshes/Projectiles/Sphere.Sphere"));
		if (SphereMesh.Succeeded()) {
			ProjectileMeshComponent->SetStaticMesh(SphereMesh.Object);
		}

		// Then Set the mesh to the component
		static ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("/Game/Materials/M_Projecctile.M_Projecctile"));
		if (SphereMesh.Succeeded()) {
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SphereMaterial.Object, ProjectileMeshComponent);
		}

		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	// Unity Destroy(3.0f);
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	// 1. FVector ShootDirection: Pass by value, least efficient.
	// 2. FVector& ShootDirection: Pass by ref, memory address. Basically an out. Can possibly change the variable outside this scope
	// 3. const FVector& ShootDirection: Pass by ref, memory address, but we can't directly change the parameter

	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShootDirection;
}

void AFPSProjectile::OnWhateverYouWantToNameIT(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Collision with only physics objects
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Colliding with something"));
}


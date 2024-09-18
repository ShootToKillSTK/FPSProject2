// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/Target.h"

ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CoinMeshComponent) {
		CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
		CoinMeshComponent->SetupAttachment(CollisionComponent);
	}
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();

}

void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("Target OnCollect Called"))
}

void ATarget::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/Collectable.h"
#include "Target.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API ATarget : public ACollectable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* CoinMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Points = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnCollectRotationRate = 1500;


	UFUNCTION()
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
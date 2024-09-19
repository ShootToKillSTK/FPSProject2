// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/FPSCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/DamageType.h"
#include "DamagingFloor.generated.h"

UCLASS()
class FPSPROJECT2_API ADamagingFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagingFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Damage amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount;

	// Collision component for detecting overlaps
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxComponent;

	// Static mesh component for the floor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* FloorMesh;

private:
	// Timer handle for periodic damage application
	FTimerHandle DamageTimerHandle;

	// Functions to handle overlap events
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	// Function to apply damage
	void ApplyDamage();

	// Boolean to check if the actor is currently on the floor
	bool bIsCharacterOnFloor;
};

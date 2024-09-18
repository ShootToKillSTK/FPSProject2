// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HUD/MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
//#include "AFPSProjectile.h"
#include "EnemyAICharacter.generated.h"

// Forward declaration of UCapsuleComponent
class UCapsuleComponent;
class AFPSProjectile;

UCLASS()
class FPSPROJECT2_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

UPROPERTY()
int Points = 10;

// Capsule component for collision detection
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
UCapsuleComponent* CollisionCapsule;

UFUNCTION()
void HitCharacter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

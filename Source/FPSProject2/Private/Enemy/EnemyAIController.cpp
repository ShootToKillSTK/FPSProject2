// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::BeginOverlap);

	if (!PawnSensing) {
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(StartingBehaviourTree);
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	AFPSCharacter* player = Cast<AFPSCharacter>(PlayerPawn);
	if (!player) return;

	// Do some logic if is player (Succeeds
	SetCanSeePlayer(true, player);

	// Retrigerable Delay
	RunTriggerableTimer();
}

void AEnemyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player)
{
	UBlackboardComponent* blackboard = GetBlackboardComponent();
	blackboard->SetValueAsBool(FName("Can See Player"), SeePlayer);
	blackboard->SetValueAsObject(FName("PlayerTarget"), Player);
}

void AEnemyAIController::RunTriggerableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}

void AEnemyAIController::HandleAttackComplete()
{
	if (GetPawn())
	{
		GetPawn()->Destroy(); // Destroy the controlled pawn
		// Optionally, destroy the AI controller itself
		// Destroy();
	}
}

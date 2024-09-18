// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Player/FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/MyHUD.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API UBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	int Points = -30;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

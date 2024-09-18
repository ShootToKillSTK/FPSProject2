// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTT_Attack.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AFPSCharacter* playerCharacter = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("PlayerTarget")));
    if (!playerCharacter) return EBTNodeResult::Failed;

    float DamageAmount = 25.0f;
    AEnemyAIController* AIOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AIOwner) return EBTNodeResult::Failed;

    playerCharacter->TakeDamage(DamageAmount, FDamageEvent(), AIOwner, AIOwner->GetPawn());
    UE_LOG(LogTemp, Warning, TEXT("Player Attacked"));

    // Notify the AI controller to handle its own destruction
    if (AIOwner)
    {
        AIOwner->HandleAttackComplete();
    }

    AMyHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AMyHUD>();
    if (HUD) {
        HUD->gameWidgetContainer->SetScoreText(Points);

        //UE_LOG(LogTemp, Warning, TEXT("Target hit, this hit"))
    }

    return EBTNodeResult::Succeeded;
}
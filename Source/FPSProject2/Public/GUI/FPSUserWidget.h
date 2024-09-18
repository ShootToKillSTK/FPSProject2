// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UButtonWidget> ButtonWidgetPrefab;

	UFUNCTION()
	void SetHealthBar(float percentage);

	UFUNCTION()
	void SetScoreText(int newScore);

	UFUNCTION()
	void ResetLevel();

private:
	int UIScore = 0;
};

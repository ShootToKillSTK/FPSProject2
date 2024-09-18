// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"



void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0f);
	SetScoreText(0);

	//if (ButtonWidgetPrefab) {
	//	for (int i = 0; i < 4; i++) {
	//		UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
	//		ButtonContainer->AddChild(widget);

	//		UButtonWidget* button = Cast<UButtonWidget>(widget); // Get Component in Unity
	//		button->SetText(i);
	//	}
	//}
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);

	if (percentage <= 0.0f)
	{
		// Call the function to reset the level
		ResetLevel();
	}
}

void UFPSUserWidget::SetScoreText(int amount)
{
	if (!ScoreText) return;

	UIScore += amount;
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(UIScore)));
}

void UFPSUserWidget::ResetLevel()
{
	// Get the current level's name
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

	// Restart the current level
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}
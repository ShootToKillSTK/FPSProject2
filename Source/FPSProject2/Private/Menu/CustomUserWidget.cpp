// Fill out your copyright notice in the Description page of Project Settings.




#include "Menu/CustomUserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

void UCustomUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButtonText->SetText(FText::FromString("Play"));
	PlayButton->OnClicked.AddDynamic(this, &UCustomUserWidget::Play);


	QuitButtonText->SetText(FText::FromString("Quit"));
	QuitButton->OnClicked.AddDynamic(this, &UCustomUserWidget::Quit);
}


void UCustomUserWidget::Play()
{
	// Ensure the game mode is correctly casted and call StartGame method
	AMenuGameModeBase* MenuGameMode = Cast<AMenuGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (MenuGameMode)
	{
		MenuGameMode->StartGame();
	}
}

void UCustomUserWidget::Quit()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
    }
}

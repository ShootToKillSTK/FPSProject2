// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void Play();

	UFUNCTION()
	void Quit();

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayButtonText;


	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitButtonText;
	virtual void NativeConstruct() override;
};

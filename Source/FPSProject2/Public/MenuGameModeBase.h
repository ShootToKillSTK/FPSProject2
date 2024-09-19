// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API AMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void StartGame();

protected:
	// The Widget Class to use for our Menu UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> MenuWidgetClass;

private:
	// The instance of the Widget that we create
	UPROPERTY()
	class UUserWidget* MenuWidget;
};

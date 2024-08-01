// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Slate/SSettingWidget.h"
#include "GUI/FPSUserWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT2_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	// Slate
	TSharedPtr<class SSettingWidget> settingWidget;
	TSharedPtr<class SWidget> menuWidgetContainer;

	void ShowSettingMenu();
	void RemoveSettingMenu();

	// UMG
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UFPSUserWidget> gameMenuWidget;
	UFPSUserWidget* gameWidgetContainer;

	void ShowMenu(TSubclassOf<UFPSUserWidget> newGameMenu);

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};

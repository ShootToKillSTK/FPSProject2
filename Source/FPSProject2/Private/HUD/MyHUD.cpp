// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MyHUD.h"
#include "Widgets/SWeakWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowMenu(gameMenuWidget);
	//ShowSettingMenu();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!CrosshairTexture) return;

	// 1. Calculate the center point of the screen
	FVector2D Center(Canvas->ClipX * 0.5, Canvas->ClipY * 0.5);

	// 2. Set the crosshair pivot to the center
	float CrosshairhalfWidth = (CrosshairTexture->GetSurfaceWidth() * 0.5);
	float CrosshairHalfHeight = (CrosshairTexture->GetSurfaceHeight() * 0.5);
	FVector2D CrosshairDrawPos(Center.X - CrosshairhalfWidth, Center.Y - CrosshairHalfHeight);

	// 3. Draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPos, CrosshairTexture->GetResource(), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AMyHUD::ShowSettingMenu()
{
	if (GEngine && GEngine->GameViewport) {
		settingWidget = SNew(SSettingWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(menuWidgetContainer, SWeakWidget).PossiblyNullContent(settingWidget.ToSharedRef()));

		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMyHUD::RemoveSettingMenu()
{
	if (GEngine && GEngine->GameViewport && menuWidgetContainer.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(menuWidgetContainer.ToSharedRef());
	}

	if (PlayerOwner) {
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}

void AMyHUD::ShowMenu(TSubclassOf<UFPSUserWidget> newGameMenu)
{
	if (gameWidgetContainer) {
		gameWidgetContainer->RemoveFromParent();
		gameWidgetContainer = nullptr;
	}

	if (newGameMenu) {
		gameWidgetContainer = CreateWidget<UFPSUserWidget>(GetWorld(), newGameMenu);
		gameWidgetContainer->AddToViewport();
	}
}

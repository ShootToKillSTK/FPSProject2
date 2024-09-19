#include "MenuGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Ensure the widget class is set (can be done in editor or code)
	if (MenuWidgetClass)
	{
		// Create the widget instance
		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);

		// Add the widget to the viewport
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();

			/////
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
}

void AMenuGameModeBase::StartGame()
{
	// Switch to game mode
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		UGameplayStatics::OpenLevel(GetWorld(), FName("FPSMap"));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FPSPROJECT2_API SSettingWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSettingWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AMyHUD> OwningHUD;

	FReply OnResumeClicked() const;
	FReply OnSettingsClicked() const;
	FReply OnQuitClicked() const;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};

// Widgets.SettingsGraphicsWidget.cpp

#include "Widgets/SettingsGraphicsWidget.h"
#include "Widgets/MenuButtonWidget.h"
#include "Components/TextBlock.h"
#include "Subsystems/LocalizationSubsystem.h"
#include "Helpers/LocalizedStrings.h"
#include "Settings/GameSettings.h"

namespace LSGraphics = LocalizedStrings::MenuSettingsGraphics;

#pragma region Base

void USettingsGraphicsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckProperties();
	SubscribeToEvents();
}

void USettingsGraphicsWidget::NativeDestruct()
{
	UnsubscribeFromEvents();

	Super::NativeDestruct();
}

void USettingsGraphicsWidget::OnLanguageChanged()
{
	ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this);
	if (!Loc)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsGraphicsWidget: LocalizationSubsystem is NULL"));
		return;
	}

	if (Label_GraphicsQuality)
		Label_GraphicsQuality->SetText(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Label_Quality));

	AvailableGraphicsQualitiesLabels.Reset();
	AvailableGraphicsQualitiesLabels.Add(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Value_QualityLow));
	AvailableGraphicsQualitiesLabels.Add(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Value_QualityMedium));
	AvailableGraphicsQualitiesLabels.Add(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Value_QualityHigh));
	AvailableGraphicsQualitiesLabels.Add(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Value_QualityEpic));
	AvailableGraphicsQualitiesLabels.Add(Loc->GetText(LSGraphics::ST_UI_MenuSettingsGraphics, LSGraphics::Value_QualityCinematic));

	UpdateGraphicsQualityUIState();
}

#pragma endregion


#pragma region Current

// public 
void USettingsGraphicsWidget::SetSettingsGraphics(const FSettingsGraphics& Settings)
{
	CurrentGraphicsQuality = Settings.GraphicsQuality;
	PendingGraphicsQuality = Settings.GraphicsQuality;

	UpdateGraphicsQualityUIState();
}

FSettingsGraphics USettingsGraphicsWidget::GetSettingsGraphics() const
{
	FSettingsGraphics Result;
	Result.GraphicsQuality = PendingGraphicsQuality;

	return Result;
}

void USettingsGraphicsWidget::Confirm()
{
	CurrentGraphicsQuality = PendingGraphicsQuality;
}

void USettingsGraphicsWidget::Cancel()
{
	PendingGraphicsQuality = CurrentGraphicsQuality;

	UpdateGraphicsQualityUIState();
}

// protected
void USettingsGraphicsWidget::OnGraphicsQualityPrevClicked()
{
	ChangeGraphicsQuality(-1);
}

void USettingsGraphicsWidget::OnGraphicsQualityNextClicked()
{
	ChangeGraphicsQuality(1);
}

// private 
void USettingsGraphicsWidget::CheckProperties()
{
	ensureMsgf(Btn_GraphicsQualityPrev, TEXT("SettingsGraphicsWidget: Btn_GraphicsQualityPrev is missing"));
	ensureMsgf(Btn_GraphicsQualityNext, TEXT("SettingsGraphicsWidget: Btn_GraphicsQualityNext is missing"));
	ensureMsgf(Label_GraphicsQuality, TEXT("SettingsGraphicsWidget: Label_GraphicsQuality is missing"));
	ensureMsgf(Value_GraphicsQuality, TEXT("SettingsGraphicsWidget: Value_GraphicsQuality is missing"));
}

void USettingsGraphicsWidget::SubscribeToEvents()
{
	if (Btn_GraphicsQualityPrev)
	{
		Btn_GraphicsQualityPrev->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityPrevClicked);
		Btn_GraphicsQualityPrev->OnMenuButtonClicked.AddDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityPrevClicked);
	}

	if (Btn_GraphicsQualityNext)
	{
		Btn_GraphicsQualityNext->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityNextClicked);
		Btn_GraphicsQualityNext->OnMenuButtonClicked.AddDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityNextClicked);
	}
}

void USettingsGraphicsWidget::UnsubscribeFromEvents()
{
	if (Btn_GraphicsQualityPrev)
		Btn_GraphicsQualityPrev->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityPrevClicked);

	if (Btn_GraphicsQualityNext)
		Btn_GraphicsQualityNext->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGraphicsWidget::OnGraphicsQualityNextClicked);
}

void USettingsGraphicsWidget::ChangeGraphicsQuality(int32 IndexDiff)
{
	int32 Index = AvailableGraphicsQualities.IndexOfByKey(PendingGraphicsQuality);
	if (Index == INDEX_NONE)
		return;

	Index += IndexDiff;
	if (Index < 0 || Index >= AvailableGraphicsQualities.Num())
		return;

	PendingGraphicsQuality = AvailableGraphicsQualities[Index];
	UpdateGraphicsQualityUIState();
}

void USettingsGraphicsWidget::UpdateGraphicsQualityUIState()
{
	const int32 Index = AvailableGraphicsQualities.IndexOfByKey(PendingGraphicsQuality);
	if (Index == INDEX_NONE)
		return;

	if (Value_GraphicsQuality && AvailableGraphicsQualitiesLabels.IsValidIndex(Index))
		Value_GraphicsQuality->SetText(AvailableGraphicsQualitiesLabels[Index]);

	if (Btn_GraphicsQualityPrev)
		Btn_GraphicsQualityPrev->SetIsEnabled(Index > 0);

	if (Btn_GraphicsQualityNext)
		Btn_GraphicsQualityNext->SetIsEnabled(Index < AvailableGraphicsQualities.Num() - 1);
}

#pragma endregion

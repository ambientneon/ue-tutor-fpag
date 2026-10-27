// Widgets/SettingsGameWidget.cpp

#include "Widgets/SettingsGameWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/MenuButtonWidget.h"
#include "Settings/GameLanguage.h"
#include "Settings/GameSettings.h"
#include "Helpers/LocalizedStrings.h"
#include "Subsystems/LocalizationSubsystem.h"

#pragma region Base

// protected
void USettingsGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckProperties();
	SubscribeToEvents();
}

void USettingsGameWidget::NativeDestruct()
{
	UnsubscribeFromEvents();

	Super::NativeDestruct();
}

void USettingsGameWidget::OnLanguageChanged()
{
	ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this);
	if (!Loc)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsGameWidget: LocalizationSubsystem is NULL"));
		return;
	}

	if (Label_Lang)
		Label_Lang->SetText(Loc->GetText(
			LocalizedStrings::MenuSettingsGame::ST_UI_MenuSettingsGame,
			LocalizedStrings::MenuSettingsGame::Label_LangInterface
		));

	UpdateLanguageUIState();
}

#pragma endregion

#pragma region Current

// public
void USettingsGameWidget::SetSettingsGame(const FSettingsGame& Settings)
{
	CurrentLanguage = Settings.Language;
	PendingLanguage = Settings.Language;

	OnLanguageChanged();
}

FSettingsGame USettingsGameWidget::GetSettingsGame() const
{
	FSettingsGame Result;
	Result.Language = PendingLanguage;
	
	return Result;
}

void USettingsGameWidget::Confirm()
{
	CurrentLanguage = PendingLanguage;
}

void USettingsGameWidget::Cancel()
{
	PendingLanguage = CurrentLanguage;

	UpdateLanguageUIState();
}

// protected
void USettingsGameWidget::OnLangPrevClicked()
{
	ChangeLanguage(-1);
}

void USettingsGameWidget::OnLangNextClicked()
{
	ChangeLanguage(1);
}

// private
void USettingsGameWidget::CheckProperties()
{
	ensureMsgf(Btn_LangPrev, TEXT("SettingsGameWidget: Btn_LangPrev is missing"));
	ensureMsgf(Btn_LangNext, TEXT("SettingsGameWidget: Btn_LangNext is missing"));
	ensureMsgf(Label_Lang, TEXT("SettingsGameWidget: Label_Lang is missing"));
	ensureMsgf(Value_Lang, TEXT("SettingsGameWidget: Value_Lang is missing"));
}

void USettingsGameWidget::SubscribeToEvents()
{
	if (Btn_LangPrev)
	{
		Btn_LangPrev->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGameWidget::OnLangPrevClicked);
		Btn_LangPrev->OnMenuButtonClicked.AddDynamic(this, &USettingsGameWidget::OnLangPrevClicked);
	}

	if (Btn_LangNext)
	{
		Btn_LangNext->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGameWidget::OnLangNextClicked);
		Btn_LangNext->OnMenuButtonClicked.AddDynamic(this, &USettingsGameWidget::OnLangNextClicked);
	}
}

void USettingsGameWidget::UnsubscribeFromEvents()
{
	if (Btn_LangPrev)
		Btn_LangPrev->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGameWidget::OnLangPrevClicked);

	if (Btn_LangNext)
		Btn_LangNext->OnMenuButtonClicked.RemoveDynamic(this, &USettingsGameWidget::OnLangNextClicked);
}

void USettingsGameWidget::ChangeLanguage(int32 IndexDiff)
{
	int32 Index = AvailableLanguages.IndexOfByKey(PendingLanguage);
	if (Index == INDEX_NONE)
		return;

	Index += IndexDiff;
	if (Index < 0 || Index >= AvailableLanguages.Num())
		return;

	PendingLanguage = AvailableLanguages[Index];
	UpdateLanguageUIState();
}

void USettingsGameWidget::UpdateLanguageUIState()
{
	const int32 Index = AvailableLanguages.IndexOfByKey(PendingLanguage);
	if (Index == INDEX_NONE)
		return;

	if (Value_Lang)
		Value_Lang->SetText(GameLanguage::ToDisplayKey(PendingLanguage));

	if (Btn_LangPrev)
		Btn_LangPrev->SetIsEnabled(Index > 0);

	if (Btn_LangNext)
		Btn_LangNext->SetIsEnabled(Index < AvailableLanguages.Num() - 1);
}

#pragma endregion

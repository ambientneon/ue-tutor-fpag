// Widgets/BaseLocalizableWidget.cpp

#include "Widgets/BaseLocalizableWidget.h"
#include "Subsystems/LocalizationSubsystem.h"

#pragma region Base

// protected
void UBaseLocalizableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BindLocalizationEvents();
	OnLanguageChanged();
}

void UBaseLocalizableWidget::NativeDestruct()
{
	UnbindLocalizationEvents();

	Super::NativeDestruct();
}

#pragma endregion

#pragma region Current

// protected
void UBaseLocalizableWidget::OnLanguageChanged() {};

void UBaseLocalizableWidget::BindLocalizationEvents()
{
	if (ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this))
	{
		Loc->OnLanguageChanged.RemoveDynamic(this, &UBaseLocalizableWidget::HandleLanguageChanged);
		Loc->OnLanguageChanged.AddDynamic(this, &UBaseLocalizableWidget::HandleLanguageChanged);
	}
}

void UBaseLocalizableWidget::UnbindLocalizationEvents()
{
	if (ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this))
	{
		Loc->OnLanguageChanged.RemoveDynamic(this, &UBaseLocalizableWidget::HandleLanguageChanged);
	}
}

// private
void UBaseLocalizableWidget::HandleLanguageChanged()
{
	OnLanguageChanged();
}

#pragma endregion
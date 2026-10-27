// Widgets/SettingsMenuWidget.cpp

#include "Widgets/SettingsMenuWidget.h"
#include "Widgets/MenuButtonWidget.h"
#include "Widgets/SettingsGameWidget.h"
#include "Widgets/SettingsGraphicsWidget.h"
#include "Components/UIManagerComponent.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Subsystems/LocalizationSubsystem.h"
#include "Helpers/LocalizedStrings.h"

namespace LSCommon = LocalizedStrings::Common;
namespace LSSettings = LocalizedStrings::MenuSettings;

#pragma region Base

// protected
void USettingsMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    CheckProperties();

    SubscribeToEvents();
    SetActiveTab(ActiveTab);
    
    SetSettings();
}

void USettingsMenuWidget::NativeDestruct()
{
    UnsubscribeFromEvents();

    Super::NativeDestruct();
}

void USettingsMenuWidget::OnLanguageChanged()
{
    ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this);
    if (!Loc)
    {
        UE_LOG(LogTemp, Error, TEXT("SettingsMenuWidget: LocalizationSubsystem is NULL"));
        return;
    }

    if (Label_Title)
        Label_Title->SetText(Loc->GetText(LSSettings::ST_UI_MenuSettings, LSSettings::Title_Settings));

    if (Btn_TabGame)
        Btn_TabGame->SetButtonText(Loc->GetText(LSSettings::ST_UI_MenuSettings, LSSettings::Tab_Game));

    if (Btn_TabGraphics)
        Btn_TabGraphics->SetButtonText(Loc->GetText(LSSettings::ST_UI_MenuSettings, LSSettings::Tab_Graphics));

    if (Btn_Confirm)
        Btn_Confirm->SetButtonText(Loc->GetText(LSCommon::ST_UI_Common, LSCommon::Label_Confirm));

    if (Btn_Cancel)
        Btn_Cancel->SetButtonText(Loc->GetText(LSCommon::ST_UI_Common, LSCommon::Label_Cancel));
}

#pragma endregion


#pragma region Current

// public
void USettingsMenuWidget::SetUIManager(UUIManagerComponent* InUIManager)
{
    this->UIManager = InUIManager;

    SetSettings();
}

// protected
void USettingsMenuWidget::OnTabGameClicked()
{
    SetActiveTab(ESettingsTab::Game);
}

void USettingsMenuWidget::OnTabGraphicsClicked()
{
    SetActiveTab(ESettingsTab::Graphics);
}

void USettingsMenuWidget::OnConfirmClicked()
{
    if (!UIManager)
        return;

    if (Settings_Game)
    {
        UIManager->HandleSettingsGameConfirm(Settings_Game->GetSettingsGame());
        Settings_Game->Confirm();
    }

    if (Settings_Graphics)
    {
        UIManager->HandleSettingsGraphicsConfirm(Settings_Graphics->GetSettingsGraphics());
        Settings_Graphics->Confirm();
    }
}

void USettingsMenuWidget::OnCancelClicked()
{
    if (Settings_Game)
        Settings_Game->Cancel();

    if (Settings_Graphics)
        Settings_Graphics->Cancel();
}

void USettingsMenuWidget::OnCloseClicked()
{
    if (!UIManager)
        return;

    UIManager->CloseSettings();
}


// private
void USettingsMenuWidget::CheckProperties()
{
    ensureMsgf(Label_Title, TEXT("SettingsMenuWidget: Label_Title missing"));

    ensureMsgf(Btn_TabGame, TEXT("SettingsMenuWidget: Button_TabGame missing"));
    ensureMsgf(Btn_TabGraphics, TEXT("SettingsMenuWidget: Button_TabGraphics missing"));
    
    ensureMsgf(Switcher_Content, TEXT("SettingsMenuWidget: Switcher_Content missing"));
    
    ensureMsgf(Btn_Confirm, TEXT("SettingsMenuWidget: Button_Confirm missing"));
    ensureMsgf(Btn_Cancel, TEXT("SettingsMenuWidget: Button_Cancel missing"));
    ensureMsgf(Btn_Close, TEXT("SettingsMenuWidget: Button_Close missing"));

    ensureMsgf(Settings_Game, TEXT("SettingsMenuWidget: Settings_Game missing"));
    ensureMsgf(Settings_Graphics, TEXT("SettingsMenuWidget: Settings_Graphics missing"));
}

void USettingsMenuWidget::SetSettings()
{
    if (!ensure(UIManager))
        return;

    if (Settings_Game)
        Settings_Game->SetSettingsGame(UIManager->GetSettingsGame());

    if (Settings_Graphics)
        Settings_Graphics->SetSettingsGraphics(UIManager->GetSettingsGraphics());
}

void USettingsMenuWidget::SubscribeToEvents()
{
    if (Btn_TabGame)
    {
        Btn_TabGame->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnTabGameClicked);
        Btn_TabGame->OnMenuButtonClicked.AddDynamic(this, &USettingsMenuWidget::OnTabGameClicked);
    }

    if (Btn_TabGraphics)
    {
        Btn_TabGraphics->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnTabGraphicsClicked);
        Btn_TabGraphics->OnMenuButtonClicked.AddDynamic(this, &USettingsMenuWidget::OnTabGraphicsClicked);
    }

    if (Btn_Confirm)
    {
        Btn_Confirm->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnConfirmClicked);
        Btn_Confirm->OnMenuButtonClicked.AddDynamic(this, &USettingsMenuWidget::OnConfirmClicked);
    }

    if (Btn_Cancel)
    {
        Btn_Cancel->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnCancelClicked);
        Btn_Cancel->OnMenuButtonClicked.AddDynamic(this, &USettingsMenuWidget::OnCancelClicked);
    }

    if (Btn_Close)
    {
        Btn_Close->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnCloseClicked);
        Btn_Close->OnMenuButtonClicked.AddDynamic(this, &USettingsMenuWidget::OnCloseClicked);
    }
}

void USettingsMenuWidget::UnsubscribeFromEvents()
{
    if (Btn_TabGame)
        Btn_TabGame->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnTabGameClicked);

    if (Btn_TabGraphics)
        Btn_TabGraphics->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnTabGraphicsClicked);

    if (Btn_Confirm)
        Btn_Confirm->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnConfirmClicked);

    if (Btn_Cancel)
        Btn_Cancel->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnCancelClicked);

    if (Btn_Close)
        Btn_Close->OnMenuButtonClicked.RemoveDynamic(this, &USettingsMenuWidget::OnCloseClicked);
}

void USettingsMenuWidget::SetActiveTab(ESettingsTab SettingsTab)
{
    ActiveTab = SettingsTab;
    
    if (Switcher_Content)
        Switcher_Content->SetActiveWidgetIndex(static_cast<int32>(ActiveTab));

    if (Btn_TabGame)
        Btn_TabGame->SetButtonSelected(ActiveTab == ESettingsTab::Game);

    if (Btn_TabGraphics)
        Btn_TabGraphics->SetButtonSelected(ActiveTab == ESettingsTab::Graphics);
}

#pragma endregion

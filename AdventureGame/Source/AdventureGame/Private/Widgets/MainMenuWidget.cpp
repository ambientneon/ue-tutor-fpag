// Widgets/MainMenuWidget.h

#include "Widgets/MainMenuWidget.h"
#include "Widgets/MenuButtonWidget.h"
#include "Components/UIManagerComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Helpers/LocalizedStrings.h"
#include "Subsystems/LocalizationSubsystem.h"

namespace LSMain = LocalizedStrings::MenuMain;

#pragma region Base

// protected
void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckProperties();
	SubscribeToEvents();
}

void UMainMenuWidget::NativeDestruct()
{
	UnsubscribeFromEvents();

	Super::NativeDestruct();
}

void UMainMenuWidget::OnLanguageChanged()
{
	ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this);
	if (!Loc)
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenuWidget: LocalizationSubsystem is NULL"));
		return;
	}

	if (Btn_Continue)
		Btn_Continue->SetButtonText(Loc->GetText(LSMain::ST_UI_MenuMain, LSMain::Label_Continue));

	if (Btn_NewGame)  
		Btn_NewGame->SetButtonText(Loc->GetText(LSMain::ST_UI_MenuMain, LSMain::Label_NewGame));
	
	if (Btn_Settings) 
		Btn_Settings->SetButtonText(Loc->GetText(LSMain::ST_UI_MenuMain, LSMain::Label_Settings));
	
	if (Btn_Quit)     
		Btn_Quit->SetButtonText(Loc->GetText(LSMain::ST_UI_MenuMain, LSMain::Label_Quit));
}

#pragma endregion


#pragma region Current

// public
void UMainMenuWidget::SetUIManager(UUIManagerComponent* InUIManager)
{
	this->UIManager = InUIManager;
}

// protected
void UMainMenuWidget::OnNewGameClicked()
{
	UWorld* World = GetWorld();
	if (!World)
		return;

	UGameplayStatics::OpenLevel(World, FName(*World->GetName()));
}

void UMainMenuWidget::OnContinueClicked()
{
	if (!UIManager)
		return;

	UIManager->CloseMainMenu();
}

void UMainMenuWidget::OnSettingsClicked()
{
	if (!UIManager)
		return;

	UIManager->OpenSettings();
}

void UMainMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

// private
void UMainMenuWidget::CheckProperties()
{
	ensureMsgf(Btn_Continue, TEXT("MainMenuWidget: Btn_Continue missing"));
	ensureMsgf(Btn_NewGame, TEXT("MainMenuWidget: Btn_NewGame missing"));
	ensureMsgf(Btn_Settings, TEXT("MainMenuWidget: Btn_Settings missing"));
	ensureMsgf(Btn_Quit, TEXT("MainMenuWidget: Btn_Quit missing"));
}

void UMainMenuWidget::SubscribeToEvents()
{
	if (Btn_NewGame)
	{
		Btn_NewGame->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnNewGameClicked);
		Btn_NewGame->OnMenuButtonClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	}

	if (Btn_Continue)
	{
		Btn_Continue->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnContinueClicked);
		Btn_Continue->OnMenuButtonClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
	}

	if (Btn_Settings)
	{
		Btn_Settings->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnSettingsClicked);
		Btn_Settings->OnMenuButtonClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);
	}

	if (Btn_Quit)
	{
		Btn_Quit->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnQuitClicked);
		Btn_Quit->OnMenuButtonClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::UnsubscribeFromEvents()
{
	if (Btn_NewGame)
		Btn_NewGame->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnNewGameClicked);

	if (Btn_Continue)
		Btn_Continue->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnContinueClicked);

	if (Btn_Settings)
		Btn_Settings->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnSettingsClicked);

	if (Btn_Quit)
		Btn_Quit->OnMenuButtonClicked.RemoveDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

#pragma endregion

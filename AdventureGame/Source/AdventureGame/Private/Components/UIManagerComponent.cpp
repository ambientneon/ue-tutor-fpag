// Components/UIManagerComponent.cpp

#include "Components/UIManagerComponent.h"
#include "Widgets/MenuWidget.h"
#include "Widgets/MainMenuWidget.h"
#include "Widgets/SettingsMenuWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "GameFramework/GameUserSettings.h"
#include "Subsystems/LocalizationSubsystem.h"
#include "Settings/GameLanguage.h"
#include "Settings/GameSettings.h"

#pragma region Base

// protected
void UUIManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    CheckProperties();

    UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
    if (ensureMsgf(Settings, TEXT("UIManager: Settings is not get")))
    {
        const int32 Level = FMath::Clamp(Settings->GetOverallScalabilityLevel(), 0, 4);
        SettingsGraphics.GraphicsQuality = static_cast<EGameGraphicsQuality>(Level);
    }

    if (ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this))
    {
        SettingsGame.Language = Loc->GetLanguage();
    }

    SetupInput();
}

#pragma endregion


#pragma region Current

// public
UUIManagerComponent::UUIManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUIManagerComponent::ToggleMainMenu()
{
    if (bIsGamePaused)
    {
        CloseMainMenu();
    }
    else
    {
        OpenMainMenu();
    }
}

void UUIManagerComponent::OpenMainMenu()
{
    if (!MenuClass || !MainMenuClass)
        return;

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
    if (!ensure(PlayerController))
        return;

    if (!MenuWidget)
    {
        MenuWidget = CreateWidget<UMenuWidget>(PlayerController, MenuClass);
        if (!MenuWidget)
            return;
    }

    if (!MainMenuWidget)
    {
        MainMenuWidget = CreateWidget<UMainMenuWidget>(PlayerController, MainMenuClass);
        if (!MainMenuWidget)
            return;

        MainMenuWidget->SetUIManager(this);
    }

    if(!MenuWidget->IsInViewport())
        MenuWidget->AddToViewport(100);

    MenuWidget->PushContent(MainMenuWidget);
    
    PlayerController->SetShowMouseCursor(true);
    PlayerController->SetInputMode(FInputModeGameAndUI());

    UGameplayStatics::SetGamePaused(GetWorld(), true);
    bIsGamePaused = true;
}

void UUIManagerComponent::CloseMainMenu()
{
    CloseSettings();

    if (MenuWidget)
    {
        MenuWidget->ClearContent();
        MenuWidget->RemoveFromParent();
    }

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
    if (ensure(PlayerController))
    {
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    UGameplayStatics::SetGamePaused(GetWorld(), false);
    bIsGamePaused = false;
}

void UUIManagerComponent::OpenSettings()
{
    if (!MenuWidget || !SettingsMenuClass)
        return;

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
    if (!ensure(PlayerController))
        return;

    if (!MenuWidget->IsInViewport())
        OpenMainMenu();

    if (!SettingsWidget)
    {
        SettingsWidget = CreateWidget<USettingsMenuWidget>(PlayerController, SettingsMenuClass);
        if (!SettingsWidget)
            return;
    }

    SettingsWidget->SetUIManager(this);
    MenuWidget->PushContent(SettingsWidget);
}

void UUIManagerComponent::CloseSettings()
{
    if (!MenuWidget || !SettingsWidget)
        return;

    if (MenuWidget->GetTopContent() == SettingsWidget)
    {
        MenuWidget->PopContent();
    }
    else
    {
        SettingsWidget->RemoveFromParent();
    }
}

void UUIManagerComponent::HandleSettingsGameConfirm(const FSettingsGame& Settings)
{
    SettingsGame = Settings;

    ULocalizationSubsystem* Loc = ULocalizationSubsystem::Get(this);
    if (!Loc)
    {
        UE_LOG(LogTemp, Error, TEXT("UIManagerComponent: LocalizationSubsystem not found"));
        return;
    }

    Loc->SetLanguage(SettingsGame.Language);
}

void UUIManagerComponent::HandleSettingsGraphicsConfirm(const FSettingsGraphics& Settings)
{
    SettingsGraphics = Settings;

    UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
    if (!ensure(GameUserSettings))
        return;

    const int32 Level = FMath::Clamp(static_cast<int32>(SettingsGraphics.GraphicsQuality), 0, 4);
    GameUserSettings->SetOverallScalabilityLevel(static_cast<int32>(Level));
    GameUserSettings->SaveSettings();
    GameUserSettings->ApplySettings(true);
}

// private
void UUIManagerComponent::CheckProperties()
{
    ensureMsgf(MenuAction, TEXT("UIManagerComponent: MenuAction missing"));
    ensureMsgf(MenuClass, TEXT("UIManagerComponent: MenuClass missing"));
    ensureMsgf(MainMenuClass, TEXT("UIManagerComponent: MainMenuClass missing"));
    ensureMsgf(SettingsMenuClass, TEXT("UIManagerComponent: SettingsMenuClass missing"));
}

void UUIManagerComponent::SetupInput()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
    if (!ensure(PlayerController) || !PlayerController->InputComponent)
        return;

    UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
    if (!ensure(EIComp))
        return;

    EIComp->BindAction(MenuAction, ETriggerEvent::Started, this, &UUIManagerComponent::OnMenuActionTriggered);
}

void UUIManagerComponent::OnMenuActionTriggered()
{
    ToggleMainMenu();
}

#pragma endregion
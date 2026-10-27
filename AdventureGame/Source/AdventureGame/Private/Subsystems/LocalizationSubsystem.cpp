// Subsystems/LocalizationSubsystem.cpp

#include "Subsystems/LocalizationSubsystem.h"
#include "Engine/GameInstance.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/Internationalization.h"
#include "Helpers/LocalizedStrings.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Settings/GameLanguage.h"

#pragma region Base

// public
void ULocalizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    LoadAllStringTables();
    LoadLanguageFromConfig();

    ApplyLanguageIfInGame(CurrentLanguage);
}

#pragma endregion

#pragma region Current

// public
ULocalizationSubsystem* ULocalizationSubsystem::Get(const UObject* WorldContext)
{
    if (!WorldContext)
        return nullptr;

    const UWorld* World = WorldContext->GetWorld();
    if (!World)
        return nullptr;

    const UGameInstance* GameInstance = World->GetGameInstance();
    if (!GameInstance)
        return nullptr;

    return GameInstance->GetSubsystem<ULocalizationSubsystem>();
}

FText ULocalizationSubsystem::GetText(FName TableShortName, const FString& Key) const
{
    if (const TObjectPtr<UStringTable>* Found = TablesByShortName.Find(TableShortName))
    {
        if (UStringTable* Table = Found->Get())
        {
            // Всегда реальный ID из загруженного ассета
            return FText::FromStringTable(
                Table->GetStringTableId(),
                Key,
                EStringTableLoadingPolicy::FindOrLoad
            );
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Localization: unknown table [%s] key [%s]"),
        *TableShortName.ToString(), *Key);

    return FText::GetEmpty();
}

void ULocalizationSubsystem::SetLanguage(const EGameLanguage& Language)
{
    CurrentLanguage = Language;

    SaveLanguageToConfig(CurrentLanguage);
    ApplyLanguageIfInGame(CurrentLanguage);
    
    OnLanguageChanged.Broadcast();
}

// private
void ULocalizationSubsystem::RegisterTable(FName ShortName)
{
    // /Game/.../LocalizedStrings/ST_UI_Common.ST_UI_Common
    const FString Name = ShortName.ToString();
    const FString Path = FString::Printf(TEXT("/Game/AdventureGame/Data/LocalizedStrings/%s.%s"), *Name, *Name );

    UStringTable* Table = LoadObject<UStringTable>(nullptr, *Path);
    if (!Table)
    {
        UE_LOG(LogTemp, Error, TEXT("Localization: failed to load %s"), *Path);
        return;
    }

    TablesByShortName.Add(ShortName, Table);

    UE_LOG(LogTemp, Log, TEXT("Localization: [%s] -> real ID [%s]"), *Name, *Table->GetStringTableId().ToString());
}

void ULocalizationSubsystem::LoadAllStringTables()
{
    TablesByShortName.Reset();

    RegisterTable(LocalizedStrings::Common::ST_UI_Common);
    RegisterTable(LocalizedStrings::MenuMain::ST_UI_MenuMain);
    RegisterTable(LocalizedStrings::MenuSettings::ST_UI_MenuSettings);
    RegisterTable(LocalizedStrings::MenuSettingsGame::ST_UI_MenuSettingsGame);
    RegisterTable(LocalizedStrings::MenuSettingsGraphics::ST_UI_MenuSettingsGraphics);
}

void ULocalizationSubsystem::LoadLanguageFromConfig()
{
    FString Saved;
    if (GConfig->GetString(TEXT("AdventureGame"), TEXT("Language"), Saved, GGameUserSettingsIni))
    {
        CurrentLanguage = GameLanguage::FromCultureCode(Saved);
        UE_LOG(LogTemp, Log, TEXT("Localization: loaded from config → %s"), *Saved);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Localization: no config, using default → %s"), *GameLanguage::ToCultureCode(CurrentLanguage));
    }
}

void ULocalizationSubsystem::SaveLanguageToConfig(const EGameLanguage& Language) const
{
    GConfig->SetString(TEXT("AdventureGame"), TEXT("Language"), *GameLanguage::ToCultureCode(Language), GGameUserSettingsIni);
    GConfig->Flush(false, GGameUserSettingsIni);
}

void ULocalizationSubsystem::ApplyLanguageIfInGame(const EGameLanguage& Language)
{
#if WITH_EDITOR
    if (GIsEditor && !GIsPlayInEditorWorld)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Localization: skipped SetCurrentCulture (pure Editor)"));
        return;
    }
#endif

    if (UWorld* World = GetWorld())
    {
        if (!World->IsGameWorld())
        {
            UE_LOG(LogTemp, Verbose, TEXT("Localization: skipped SetCurrentCulture (not GameWorld)"));
            return;
        }
    }

    const FString CultureCode = GameLanguage::ToCultureCode(Language);
    const bool bSuccess = FInternationalization::Get().SetCurrentCulture(CultureCode);

    const FString ActualCulture = UKismetInternationalizationLibrary::GetCurrentCulture();

    UE_LOG(LogTemp, Log, TEXT("Localization: SetCurrentCulture [%s]  Success=%d  Actual=[%s]"),
        *CultureCode,
        bSuccess ? 1 : 0,
        *ActualCulture
    );
}

#pragma endregion
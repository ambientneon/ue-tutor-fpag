// Subsystems/LocalizationSubsystem.h

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Settings/GameLanguage.h"
#include "LocalizationSubsystem.generated.h"

class UStringTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLanguageChanged);

UCLASS()
class ADVENTUREGAME_API ULocalizationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

    // base
public:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Localization Subsystem|Localization")
    EGameLanguage CurrentLanguage = EGameLanguage::Russian;


    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	
    // current
public:
    UPROPERTY(BlueprintAssignable, Category = "Localization Subsystem|Localization")
    FOnGameLanguageChanged OnLanguageChanged;

    static ULocalizationSubsystem* Get(const UObject* WorldContext);

    
    UFUNCTION(BlueprintCallable, Category = "Localization Subsystem|Localization")
    FText GetText(FName TableId, const FString& Key) const;

    UFUNCTION(BlueprintCallable, Category = "Localization Subsystem|Localization")
    void SetLanguage(const EGameLanguage& Language);

    UFUNCTION(BlueprintPure, Category = "Localization Subsystem|Localization")
    EGameLanguage GetLanguage() const { 
        return CurrentLanguage; 
    }

private:
    UPROPERTY()
    TMap<FName, TObjectPtr<UStringTable>> TablesByShortName;

    
    void RegisterTable(FName ShortName);
    void LoadAllStringTables();

    void LoadLanguageFromConfig();
    void SaveLanguageToConfig(const EGameLanguage& Language) const;
    
    void ApplyLanguageIfInGame(const EGameLanguage& Language);
};

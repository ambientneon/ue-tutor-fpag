// Components/UIManagerComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Settings/GameSettings.h"
#include "UIManagerComponent.generated.h"

class UInputAction;
class UMenuWidget;
class UMainMenuWidget;
class USettingsMenuWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVENTUREGAME_API UUIManagerComponent : public UActorComponent
{
    GENERATED_BODY()

    // base
protected:
    virtual void BeginPlay() override;


    // current
public:
    UUIManagerComponent();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | UI")
    void ToggleMainMenu();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | UI")
    void OpenMainMenu();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | UI")
    void CloseMainMenu();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | UI")
    void OpenSettings();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | UI")
    void CloseSettings();

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | Settings")
    void HandleSettingsGameConfirm(const FSettingsGame& Settings);

    UFUNCTION(BlueprintCallable, Category = "UI Manager Component | Settings")
    void HandleSettingsGraphicsConfirm(const FSettingsGraphics& Settings);

    UFUNCTION(BlueprintPure, Category = "UI Manager Component | Settings")
    FSettingsGame GetSettingsGame() const
    {
        return SettingsGame;
    }

    UFUNCTION(BlueprintPure, Category = "UI Manager Component | Settings")
    FSettingsGraphics GetSettingsGraphics() const
    {
        return SettingsGraphics;
    }

    UFUNCTION(BlueprintPure, Category = "UI Manager Component | UI")
    bool IsPaused() const
    {
        return bIsGamePaused;
    }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Input")
    TObjectPtr<UInputAction> MenuAction;

    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Widgets")
    TSubclassOf<UMenuWidget> MenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Widgets")
    TSubclassOf<UMainMenuWidget> MainMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Widgets")
    TSubclassOf<USettingsMenuWidget> SettingsMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Settings")
    FSettingsGame SettingsGame;

    UPROPERTY(EditDefaultsOnly, Category = "UI Manager Component | Settings")
    FSettingsGraphics SettingsGraphics;

private:
    UPROPERTY()
    TObjectPtr<UMenuWidget> MenuWidget;

    UPROPERTY()
    TObjectPtr<UMainMenuWidget> MainMenuWidget;

    UPROPERTY()
    TObjectPtr<USettingsMenuWidget> SettingsWidget;

    bool bIsGamePaused = false;

    void CheckProperties();
    void SetupInput();

    UFUNCTION()
    void OnMenuActionTriggered();
};
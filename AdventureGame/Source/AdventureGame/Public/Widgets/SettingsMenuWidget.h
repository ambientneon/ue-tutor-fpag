// Widgets/SettingsMenuWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseLocalizableWidget.h"
#include "Settings/GameSettings.h"
#include "SettingsMenuWidget.generated.h"

class UUIManagerComponent;
class UMenuButtonWidget;
class UWidgetSwitcher;
class UTextBlock;
class USettingsGameWidget;
class USettingsGraphicsWidget;

UENUM(BlueprintType)
enum class ESettingsTab : uint8
{
	Game		= 0 UMETA(DisplayName = "Game"),
	Graphics	= 1 UMETA(DisplayName = "Graphics")
};

UCLASS()
class ADVENTUREGAME_API USettingsMenuWidget : public UBaseLocalizableWidget
{
	GENERATED_BODY()

	// base
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void OnLanguageChanged() override;


	// current
public:
	void SetUIManager(UUIManagerComponent* InUIManager);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_Title;

	// tabs
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_TabGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_TabGraphics;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher_Content;

	// tab contents 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USettingsGameWidget> Settings_Game;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USettingsGraphicsWidget> Settings_Graphics;

	// bottom buttons
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_Confirm;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_Cancel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_Close;


	UFUNCTION()
	void OnTabGameClicked();

	UFUNCTION()
	void OnTabGraphicsClicked();

	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCancelClicked();

	UFUNCTION()
	void OnCloseClicked();

private:
	UPROPERTY()
	TObjectPtr<UUIManagerComponent> UIManager;

	ESettingsTab ActiveTab = ESettingsTab::Game;

	void CheckProperties();
	void SetSettings();

	void SubscribeToEvents();
	void UnsubscribeFromEvents();

	void SetActiveTab(ESettingsTab SettingsTab);
};
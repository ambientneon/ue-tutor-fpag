// Widgets/MainMenuWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Widgets/BaseLocalizableWidget.h"
#include "MainMenuWidget.generated.h"

class UMenuButtonWidget;
class UUIManagerComponent;

UCLASS()
class ADVENTUREGAME_API UMainMenuWidget : public UBaseLocalizableWidget
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
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Main Menu")
	TObjectPtr<UMenuButtonWidget> Btn_NewGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Main Menu")
	TObjectPtr<UMenuButtonWidget> Btn_Continue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Main Menu")
	TObjectPtr<UMenuButtonWidget> Btn_Settings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Main Menu")
	TObjectPtr<UMenuButtonWidget> Btn_Quit;

	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnQuitClicked();

private:
	UPROPERTY()
	TObjectPtr<UUIManagerComponent> UIManager;

	void CheckProperties();

	void SubscribeToEvents();
	void UnsubscribeFromEvents();
};
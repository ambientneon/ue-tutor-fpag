// Widgets/SettingsGameWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseLocalizableWidget.h"
#include "Settings/GameLanguage.h"
#include "Settings/GameSettings.h"
#include "SettingsGameWidget.generated.h"

class UMenuButtonWidget;
class UTextBlock;

UCLASS()
class ADVENTUREGAME_API USettingsGameWidget : public UBaseLocalizableWidget
{
	GENERATED_BODY()

	// base
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void OnLanguageChanged() override;


	// current
public:
	UFUNCTION(BlueprintCallable, Category = "Settings Game")
	void SetSettingsGame(const FSettingsGame& Settings);

	UFUNCTION(BlueprintCallable, Category = "Settings Game")
	FSettingsGame GetSettingsGame() const;

	UFUNCTION(BlueprintCallable, Category = "Settings Game")
	void Confirm();

	UFUNCTION(BlueprintCallable, Category = "Settings Game")
	void Cancel();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_LangPrev;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_LangNext;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_Lang;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value_Lang;


	UFUNCTION()
	void OnLangPrevClicked();

	UFUNCTION()
	void OnLangNextClicked();

private:
	const TArray<EGameLanguage> AvailableLanguages = {
		EGameLanguage::English,
		EGameLanguage::Russian
	};

	EGameLanguage CurrentLanguage = EGameLanguage::English;
	EGameLanguage PendingLanguage = EGameLanguage::English;

	void CheckProperties();

	void SubscribeToEvents();
	void UnsubscribeFromEvents();
	
	void ChangeLanguage(int32 IndexDiff);
	void UpdateLanguageUIState();
};

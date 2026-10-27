// Widgets/SettingsGraphicsWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseLocalizableWidget.h"
#include "Settings/GameSettings.h"
#include "SettingsGraphicsWidget.generated.h"

class UMenuButtonWidget;
class UTextBlock;

UCLASS()
class ADVENTUREGAME_API USettingsGraphicsWidget : public UBaseLocalizableWidget
{
	GENERATED_BODY()

	// base
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void OnLanguageChanged() override;


	// current
public:
	UFUNCTION(BlueprintCallable, Category = "Settings Graphics")
	void SetSettingsGraphics(const FSettingsGraphics& Settings);

	UFUNCTION(BlueprintPure, Category = "Settings Graphics")
	FSettingsGraphics GetSettingsGraphics() const;

	UFUNCTION(BlueprintCallable, Category = "Settings Graphics")
	void Confirm();

	UFUNCTION(BlueprintCallable, Category = "Settings Graphics")
	void Cancel();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_GraphicsQualityPrev;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMenuButtonWidget> Btn_GraphicsQualityNext;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label_GraphicsQuality;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value_GraphicsQuality;


	UFUNCTION()
	void OnGraphicsQualityPrevClicked();

	UFUNCTION()
	void OnGraphicsQualityNextClicked();

private:
	const TArray<EGameGraphicsQuality> AvailableGraphicsQualities = {
		EGameGraphicsQuality::Low,
		EGameGraphicsQuality::Medium,
		EGameGraphicsQuality::High,
		EGameGraphicsQuality::Epic,
		EGameGraphicsQuality::Cinematic
	};
	TArray<FText> AvailableGraphicsQualitiesLabels;

	EGameGraphicsQuality CurrentGraphicsQuality = EGameGraphicsQuality::Medium;
	EGameGraphicsQuality PendingGraphicsQuality = EGameGraphicsQuality::Medium;

	void CheckProperties();

	void SubscribeToEvents();
	void UnsubscribeFromEvents();

	void ChangeGraphicsQuality(int32 IndexDiff);
	void UpdateGraphicsQualityUIState();
};
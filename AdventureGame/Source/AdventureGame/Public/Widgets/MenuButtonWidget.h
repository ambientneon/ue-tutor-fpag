// Widgets/MenuButtonWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuButtonWidget.generated.h"

class UButton;
class UTextBlock;
class USizeBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuButtonClicked);

UCLASS()
class ADVENTUREGAME_API UMenuButtonWidget : public UUserWidget
{
	GENERATED_BODY()

	// base
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Menu Button")
	FText BtnText;

	UPROPERTY(BlueprintAssignable, Category = "Menu Button")
	FOnMenuButtonClicked OnMenuButtonClicked;

	// colors: unselected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Normal")
	FSlateColor NormalColor = FLinearColor(1.f, 1.f, 1.f, 0.06f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Normal")
	FSlateColor HoveredColor = FLinearColor(1.f, 1.f, 1.f, 0.12f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Normal")
	FSlateColor PressedColor = FLinearColor(1.f, 1.f, 1.f, 0.04f);

	// colors: selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Selected")
	FSlateColor SelectedNormalColor = FLinearColor(0.45f, 0.65f, 1.f, 0.14f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Selected")
	FSlateColor SelectedHoveredColor = FLinearColor(0.50f, 0.70f, 1.f, 0.20f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Selected")
	FSlateColor SelectedPressedColor = FLinearColor(0.40f, 0.58f, 0.95f, 0.10f);

	// color for disabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Colors|Disabled")
	FSlateColor DisabledColor = FLinearColor(1.f, 1.f, 1.f, 0.03f);

	// size box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Size", meta = (ExposeOnSpawn = true))
	float ButtonWidth = 320.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Button|Size", meta = (ExposeOnSpawn = true))
	float ButtonHeight = 56.f;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UFUNCTION(BlueprintCallable, Category = "Menu Button")
	void SetButtonText(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "Menu Button")
	void SetButtonSelected(bool bInSelected);

	UFUNCTION(BlueprintCallable, Category = "Menu Button")
	void SetButtonIsEnabled(bool bInEnabled);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label;

	UFUNCTION()
	void HandleButtonClicked();

private: 
	bool bIsSelected = false;

	void UpdateAppearance();
};

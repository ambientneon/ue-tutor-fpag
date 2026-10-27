// Widgets/MenuWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UOverlay;
class UOverlaySlot;
class UBackgroundBlur;
class UBorder;

UCLASS()
class ADVENTUREGAME_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	// current
public:
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PushContent(UUserWidget* Content);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PopContent();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ClearContent();

	UFUNCTION(BlueprintPure, Category = "Menu")
	UUserWidget* GetTopContent() const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay_Content;

private:
	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> ContentStack;

	void RefreshContentVisibility();
};

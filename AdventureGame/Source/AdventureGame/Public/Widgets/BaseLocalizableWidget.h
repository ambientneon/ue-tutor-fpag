// Widgets/BaseLocalizableWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseLocalizableWidget.generated.h"

UCLASS()
class ADVENTUREGAME_API UBaseLocalizableWidget : public UUserWidget
{
	GENERATED_BODY()

	// base 
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	// current:
protected:
	virtual void OnLanguageChanged();
	virtual void BindLocalizationEvents();
	virtual void UnbindLocalizationEvents();

private:
	UFUNCTION()
	void HandleLanguageChanged();
};

// Widgets/MenuButtonWidget.cpp

#include "Widgets/MenuButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

#pragma region Base

// protected
void UMenuButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SizeBox_Root)
	{
		SizeBox_Root->SetWidthOverride(ButtonWidth);
		SizeBox_Root->SetHeightOverride(ButtonHeight);
	}

	if (Label)
	{
		Label->SetText(BtnText);
	}
}

void UMenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Label)
	{
		Label->SetText(BtnText);
	}

	if (Btn)
	{
		Btn->OnClicked.RemoveDynamic(this, &UMenuButtonWidget::HandleButtonClicked);
		Btn->OnClicked.AddDynamic(this, &UMenuButtonWidget::HandleButtonClicked);
	}

	UpdateAppearance();
}

void UMenuButtonWidget::NativeDestruct()
{
	if (Btn)
	{
		Btn->OnClicked.RemoveDynamic(this, &UMenuButtonWidget::HandleButtonClicked);
	}

	Super::NativeDestruct();
}

#pragma region

#pragma region Current

// public
void UMenuButtonWidget::SetButtonText(const FText& InText)
{
	BtnText = InText;

	if (!Label) 
		return;

	Label->SetText(BtnText);
}

void UMenuButtonWidget::SetButtonSelected(bool bInSelected)
{
	bIsSelected = bInSelected;
	UpdateAppearance();
}

void UMenuButtonWidget::SetButtonIsEnabled(bool bInEnabled)
{
	if (!Btn) 
		return;
	
	Btn->SetIsEnabled(bInEnabled);
}

// protected
void UMenuButtonWidget::HandleButtonClicked()
{
	OnMenuButtonClicked.Broadcast();
}

// private
void UMenuButtonWidget::UpdateAppearance()
{
	if (!Btn) 
		return;

	FButtonStyle Style = Btn->GetStyle();

	auto ApplyTint = [&](FSlateBrush& Brush, const FSlateColor& Color)
	{
		Brush.TintColor = Color;
	};

	if (bIsSelected)
	{
		ApplyTint(Style.Normal, SelectedNormalColor);
		ApplyTint(Style.Hovered, SelectedHoveredColor);
		ApplyTint(Style.Pressed, SelectedPressedColor);
	}
	else
	{
		ApplyTint(Style.Normal, NormalColor);
		ApplyTint(Style.Hovered, HoveredColor);
		ApplyTint(Style.Pressed, PressedColor);
	}

	ApplyTint(Style.Disabled, DisabledColor);

	Btn->SetStyle(Style);

	if (Label)
	{
		const FLinearColor TextCol = bIsSelected
			? FLinearColor(0.92f, 0.95f, 1.f, 1.f)
			: FLinearColor(0.90f, 0.92f, 0.96f, 0.92f);
		Label->SetColorAndOpacity(FSlateColor(TextCol));
	}
}

#pragma endregion

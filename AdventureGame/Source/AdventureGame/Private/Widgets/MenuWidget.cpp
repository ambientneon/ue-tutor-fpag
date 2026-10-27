// Widgets/MenuWidget.cpp

#include "Widgets/MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#pragma region Current

// public
void UMenuWidget::PushContent(UUserWidget* Content)
{
	if (!Content || !Overlay_Content)
		return;

	if (ContentStack.Num() > 0 && ContentStack.Last() == Content)
	{
		RefreshContentVisibility();
		return;
	}

	ContentStack.Remove(Content);

	if (Content->GetParent() != Overlay_Content)
	{
		Overlay_Content->AddChildToOverlay(Content);
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Content->Slot))
		{
			OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(VAlign_Fill);
		}
	}

	ContentStack.Add(Content);
	RefreshContentVisibility();
}

void UMenuWidget::PopContent()
{
	if (ContentStack.Num() == 0 || !Overlay_Content)
		return;

	UUserWidget* Top = ContentStack.Pop();
	if (Top)
		Top->RemoveFromParent();

	RefreshContentVisibility();
}

void UMenuWidget::ClearContent()
{
	while (ContentStack.Num() > 0)
	{
		PopContent();
	}
}

UUserWidget* UMenuWidget::GetTopContent() const
{
	return ContentStack.Num() > 0 ? ContentStack.Last().Get() : nullptr;
}

// private
void UMenuWidget::RefreshContentVisibility()
{
	for (int32 i = 0; i < ContentStack.Num(); ++i)
	{
		if (UUserWidget* W = ContentStack[i].Get())
		{
			const bool bTop = (i == ContentStack.Num() - 1);
			W->SetVisibility(bTop
				? ESlateVisibility::SelfHitTestInvisible
				: ESlateVisibility::Collapsed);
		}
	}
}

#pragma endregion
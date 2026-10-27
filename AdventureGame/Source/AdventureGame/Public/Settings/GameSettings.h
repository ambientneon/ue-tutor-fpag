// Settings/GameSettings.h

#pragma once

#include "CoreMinimal.h"
#include "Settings/GameLanguage.h"
#include "GameSettings.generated.h"

UENUM(BlueprintType)
enum class EGameGraphicsQuality : uint8
{
    Low         = 0 UMETA(DisplayName = "Low"),
    Medium      = 1 UMETA(DisplayName = "Medium"),
    High        = 2 UMETA(DisplayName = "High"),
    Epic        = 3 UMETA(DisplayName = "Epic"),
    Cinematic   = 4 UMETA(DisplayName = "Cinematic")
};

USTRUCT(BlueprintType)
struct FSettingsGame
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings Game")
    EGameLanguage Language = EGameLanguage::English;
};

USTRUCT(BlueprintType)
struct FSettingsGraphics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings Graphics")
    EGameGraphicsQuality GraphicsQuality = EGameGraphicsQuality::Medium;
};
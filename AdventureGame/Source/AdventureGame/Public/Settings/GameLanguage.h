// Settings/GameLanguage.h

#pragma once

#include "CoreMinimal.h"
#include "GameLanguage.generated.h"

UENUM(BlueprintType)
enum class EGameLanguage : uint8
{
    English     = 0 UMETA(DisplayName = "English"),
    Russian     = 1 UMETA(DisplayName = "Russian")
};

namespace GameLanguage
{
    inline FString ToCultureCode(EGameLanguage Lang)
    {
        switch (Lang)
        {
            case EGameLanguage::Russian:
                return TEXT("ru-RU");

            case EGameLanguage::English:
                return TEXT("en");

            default:
                return TEXT("en");
        }
    }

    inline EGameLanguage FromCultureCode(const FString& Culture)
    {
        if (Culture.StartsWith(TEXT("ru")))
            return EGameLanguage::Russian;

        return EGameLanguage::English;
    }

    inline FText ToDisplayKey(EGameLanguage Lang)
    {
        switch (Lang)
        {
            case EGameLanguage::Russian:
                return FText::FromString(TEXT("Русский"));

            default:
                return FText::FromString(TEXT("English"));
        }
    }
}
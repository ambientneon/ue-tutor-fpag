// Helpers/LocalizedStrings.h

#pragma once

#include "CoreMinimal.h"

#define UI_STRING_KEY(Name) inline const FString Name = TEXT(#Name)
#define UI_STRING_TABLE(Name) inline const FName Name = TEXT(#Name)

namespace LocalizedStrings
{
    namespace Common
    {
        UI_STRING_TABLE(ST_UI_Common);
        UI_STRING_KEY(Label_Cancel);
        UI_STRING_KEY(Label_Confirm);
        UI_STRING_KEY(Value_Lang);
    }

    namespace MenuMain
    {
        UI_STRING_TABLE(ST_UI_MenuMain);
        UI_STRING_KEY(Label_Continue);
        UI_STRING_KEY(Label_NewGame);
        UI_STRING_KEY(Label_Quit);
        UI_STRING_KEY(Label_Settings);
    }

    namespace MenuSettings
    {
        UI_STRING_TABLE(ST_UI_MenuSettings);
        UI_STRING_KEY(Title_Settings);
        UI_STRING_KEY(Tab_Game);
        UI_STRING_KEY(Tab_Graphics);
    }

    namespace MenuSettingsGame
    {
        UI_STRING_TABLE(ST_UI_MenuSettingsGame);
        UI_STRING_KEY(Label_LangInterface);
    }

    namespace MenuSettingsGraphics
    {
        UI_STRING_TABLE(ST_UI_MenuSettingsGraphics);
        UI_STRING_KEY(Label_Quality);
        UI_STRING_KEY(Value_QualityLow);
        UI_STRING_KEY(Value_QualityMedium);
        UI_STRING_KEY(Value_QualityHigh);
        UI_STRING_KEY(Value_QualityEpic);
        UI_STRING_KEY(Value_QualityCinematic);
    }
}

#undef UI_STRING_KEY
#undef UI_STRING_TABLE
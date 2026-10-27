// AdventurePlayerController.cpp

#include "AdventurePlayerController.h"
#include "Components/UIManagerComponent.h"

AAdventurePlayerController::AAdventurePlayerController()
{
	UIManagerComponent = CreateDefaultSubobject<UUIManagerComponent>(TEXT("UIManagerComponent"));
}
// AdventurePlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdventurePlayerController.generated.h"

class UUIManagerComponent;

UCLASS()
class ADVENTUREGAME_API AAdventurePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	// current
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventure Player Controller | UI")
	TObjectPtr<UUIManagerComponent> UIManagerComponent;

	AAdventurePlayerController();
};

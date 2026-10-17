#pragma once

#include "CoreMinimal.h"
#include "Pickups/EquippableToolBase.h"
#include "DartLauncher.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API ADartLauncher : public AEquippableToolBase
{
	GENERATED_BODY()
	
public:
	virtual void Use() override;

	virtual void BindInputAction(const UInputAction* InputToBind) override;
};

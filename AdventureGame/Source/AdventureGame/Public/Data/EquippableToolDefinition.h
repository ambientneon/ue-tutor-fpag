// Data/EquippableToolDefinition.h

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDefinition.h"
#include "EquippableToolDefinition.generated.h"

class AEquippableToolBase;

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API UEquippableToolDefinition : public UItemDefinition
{
	GENERATED_BODY()

	// UItemDefinition
public:
	virtual UEquippableToolDefinition* CreateItemCopy(UObject* Outer) const override;


	// current
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable Tool Definition | Tools")
	TSubclassOf<AEquippableToolBase> ToolAsset;
};

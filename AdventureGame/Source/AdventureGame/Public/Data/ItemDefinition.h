// Data/ItemDefinition.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/ItemData.h"
#include "ItemDefinition.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API UItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
	// current
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Definition | Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Definition | Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Definition | Item Data")
	FItemText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Definition | Item Data")
	TSoftObjectPtr<UStaticMesh> WorldMesh;

	virtual UItemDefinition* CreateItemCopy(UObject* Outer) const;
};

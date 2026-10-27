// Data/ItemType.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

class UItemDefinition;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Tool        = 0 UMETA(DisplayName = "Tool"),
	Consumable  = 1 UMETA(DisplayName = "Consumable")
};

USTRUCT(BlueprintType)
struct FItemText
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Text")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Text")
	FText Description;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// The ID name of this item (matches the row name).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FItemText ItemText;

	// The Data Asset item definition associated with this item.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	TSoftObjectPtr<UItemDefinition> ItemBase;
};
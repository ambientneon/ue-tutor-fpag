// Components/InventoryComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UEquippableToolDefinition;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// base
protected:
	virtual void BeginPlay() override;


	// current
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Component | Tools")
	TArray<TObjectPtr<UEquippableToolDefinition>> ToolInventory;

	UInventoryComponent();
};

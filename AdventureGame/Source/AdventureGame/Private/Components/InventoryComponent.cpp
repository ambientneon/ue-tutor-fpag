#include "Components/InventoryComponent.h"

#pragma region Public
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
#pragma endregion

#pragma region Protected
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion
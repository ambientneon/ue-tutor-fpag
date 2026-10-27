// Components/InventoryComponent.cpp

#include "Components/InventoryComponent.h"

#pragma region Base

// protected
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Current

// public
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion
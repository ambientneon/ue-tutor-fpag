// Data/EquippableToolDefinition.cpp

#include "Data/EquippableToolDefinition.h"

#pragma region Base

// public
UEquippableToolDefinition* UEquippableToolDefinition::CreateItemCopy(UObject* Outer) const
{
	if (!Outer)
	{
		Outer = GetTransientPackage();
	}

	return DuplicateObject<UEquippableToolDefinition>(this, Outer);
}

#pragma endregion

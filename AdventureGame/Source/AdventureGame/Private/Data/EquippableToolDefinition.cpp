#include "Data/EquippableToolDefinition.h"

#pragma region Public
UEquippableToolDefinition* UEquippableToolDefinition::CreateItemCopy(UObject* Outer) const
{
	if (!Outer)
	{
		Outer = GetTransientPackage();
	}

	return DuplicateObject<UEquippableToolDefinition>(this, Outer);
}
#pragma endregion

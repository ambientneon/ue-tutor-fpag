#include "Data/ItemDefinition.h"

#pragma region Public
UItemDefinition* UItemDefinition::CreateItemCopy(UObject* Outer) const
{
	UItemDefinition* ItemCopy = NewObject<UItemDefinition>(Outer);
	ItemCopy->ID = this->ID;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemText = this->ItemText;
	ItemCopy->WorldMesh = this->WorldMesh;

	return ItemCopy;
}
#pragma endregion

#include "Pickups/EquippableToolBase.h"
#include "InputMappingContext.h"
#include "AdventureCharacter.h"

#pragma region Public
AEquippableToolBase::AEquippableToolBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ToolMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ToolMesh"));
	if (!ensure(ToolMeshComponent)) { return; }
}

void AEquippableToolBase::Use() {}

void AEquippableToolBase::BindInputAction(const UInputAction* ActionToBind) {}
#pragma endregion

#pragma region Protected
void AEquippableToolBase::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion

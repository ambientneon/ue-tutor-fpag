// Pickups/EquippableToolBase.cpp

#include "Pickups/EquippableToolBase.h"
#include "InputMappingContext.h"
#include "AdventureCharacter.h"

#pragma region Base

// protected
void AEquippableToolBase::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Protected

// public
AEquippableToolBase::AEquippableToolBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ToolMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ToolMesh"));
}

void AEquippableToolBase::Use() {}

void AEquippableToolBase::BindInputAction(const UInputAction* ActionToBind) {}

#pragma endregion

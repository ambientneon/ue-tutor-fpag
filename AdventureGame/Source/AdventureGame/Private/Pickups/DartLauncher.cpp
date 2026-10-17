#include "Pickups/DartLauncher.h"
#include "AdventureCharacter.h"

#pragma region Public
void ADartLauncher::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Using the dart launcher!"));
}

void ADartLauncher::BindInputAction(const UInputAction* InputToBind)
{
	APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter);
	if (!PlayerController) { return; }

	UEnhancedInputComponent* EnhancedImputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (!EnhancedImputComponent) { return; }

	EnhancedImputComponent->BindAction(InputToBind, ETriggerEvent::Triggered, this, &ADartLauncher::Use);
}
#pragma endregion


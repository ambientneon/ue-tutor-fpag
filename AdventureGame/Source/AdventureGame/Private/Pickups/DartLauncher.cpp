#include "Pickups/DartLauncher.h"
#include "AdventureCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "Projectiles/FirstPersonProjectile.h"

#pragma region Public
void ADartLauncher::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Using the dart launcher!"));

	UWorld* const World = GetWorld();
	if (!World) { return; }
	if (!ProjectileClass) { return; }

	FVector TargetPosition = OwningCharacter->GetCameraTargetLocation();

	// get the current soxket to spawn the projectile from
	FVector SocketLocation = ToolMeshComponent->GetSocketLocation("Muzzle");
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SocketLocation, TargetPosition);
	FVector SpawnLocation = SocketLocation + UKismetMathLibrary::GetForwardVector(SpawnRotation) * 10.f;

	// set spawn collision handling override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// spawn the projectile at the muzzle
	World->SpawnActor<AFirstPersonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}

void ADartLauncher::BindInputAction(const UInputAction* InputToBind)
{
	APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
	if (!PlayerController) { return; }

	UEnhancedInputComponent* EnhancedImputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (!EnhancedImputComponent) { return; }

	EnhancedImputComponent->BindAction(InputToBind, ETriggerEvent::Triggered, this, &ADartLauncher::Use);
}
#pragma endregion
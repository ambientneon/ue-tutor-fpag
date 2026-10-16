#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "AdventureCharacter.generated.h"

class UInputAction;
class UInputComponent;
class UInputMappingContext;
class UAnimInstance;

// Categories
// "AdventureCharacter"
// "AdventureCharacter|Camera"
// "AdventureCharacter|Input"
// "AdventureCharacter|Mesh"
// "AdventureCharacter|Animation"

UCLASS(meta = (PrioritizeCategories = "AdventureCharacter"))
class ADVENTUREGAME_API AAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAdventureCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	// Offset for the first-person camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	FVector FirstPersonCameraOffset = FVector(2.8, 5.9f, 0.0f);

	// First-person primitives field of view
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	float FirstPersonFieldOfView = 70.0f;

	// First-person primitives view scale
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	float FirstPersonScale = 0.6f;

	// First-person mesh, visible only to the owning player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Mesh")
	TObjectPtr<USkeletalMeshComponent> FirstPersonMeshComponent;

	// first persion animation class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Animation")
	TSubclassOf<UAnimInstance> FirstPersonDefaultAnimationClass;


	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputMappingContext> FirstPersonContext;

	// Move Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> MoveAction;

	// Jump Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> JumpAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> LookAction;

private:
	void InitializeMeshes();
	void InitializeCamera();

	void SetupMeshes();
	void SetupAnimations();
};

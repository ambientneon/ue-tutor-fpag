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
class UItemDefinition;
class AEquippableToolBase;
class UEquippableToolDefinition;
class UInventoryComponent;

UCLASS(meta = (PrioritizeCategories = "AdventureCharacter"))
class ADVENTUREGAME_API AAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	FVector FirstPersonCameraOffset = FVector(2.8, 5.9f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	float FirstPersonFieldOfView = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Camera")
	float FirstPersonScale = 0.6f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Mesh")
	TObjectPtr<USkeletalMeshComponent> FirstPersonMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Animation")
	TSubclassOf<UAnimInstance> FirstPersonDefaultAnimationClass;

	UPROPERTY(VisibleAnywhere, Category = "AdventureCharacter|Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	AAdventureCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	bool IsToolAlreadyOwned(UEquippableToolDefinition* ToolDefinition);

	UFUNCTION()
	void AttachTool(UEquippableToolDefinition* ToolDefinition);

	UFUNCTION()
	void GiveItem(UItemDefinition* ItemDefinition);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputMappingContext> FirstPersonContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Input")
	TObjectPtr<UInputAction> UseAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AdventureCharacter|Tools")
	TObjectPtr<AEquippableToolBase> EquippedTool;

	virtual void BeginPlay() override;

private:
	void InitializeMeshes();
	void InitializeCamera();

	void SetupMeshes();
	void SetupAnimations();
};

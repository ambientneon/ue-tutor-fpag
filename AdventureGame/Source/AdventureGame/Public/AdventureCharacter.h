// AdventureCharacter.h

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

UCLASS()
class ADVENTUREGAME_API AAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

	// base
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;


	// current
public:
	UPROPERTY(VisibleAnywhere, Category = "Adventure Character | Camera")
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Adventure Character | Camera")
	FVector FirstPersonCameraOffset = FVector(2.8, 5.9f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Adventure Character | Camera")
	float FirstPersonFieldOfView = 70.0f;

	UPROPERTY(EditAnywhere, Category = "Adventure Character | Camera")
	float FirstPersonScale = 0.6f;

	UPROPERTY(VisibleAnywhere, Category = "Adventure Character | Mesh")
	TObjectPtr<USkeletalMeshComponent> FirstPersonMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Adventure Character | Animation")
	TSubclassOf<UAnimInstance> FirstPersonDefaultAnimationClass;

	UPROPERTY(VisibleAnywhere, Category = "Adventure Character | Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;


	AAdventureCharacter();

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

	UFUNCTION()
	FVector GetCameraTargetLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Character| Input")
	TObjectPtr<UInputMappingContext> FirstPersonContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Character| Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Character| Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Character| Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Character| Input")
	TObjectPtr<UInputAction> UseAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventure Character| Tools")
	TObjectPtr<AEquippableToolBase> EquippedTool;

private:
	void InitializeMeshes();
	void InitializeCamera();

	void SetupMeshes();
	void SetupAnimations();
};

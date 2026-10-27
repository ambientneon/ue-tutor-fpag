// Pickups/EquippableToolBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimBlueprint.h"
#include "EnhancedInputSubsystems.h"
#include "EquippableToolBase.generated.h"

class AAdventureCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API AEquippableToolBase : public AActor
{
	GENERATED_BODY()

	// base 
protected:
	virtual void BeginPlay() override;


	// current
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable Tool Base")
	TSubclassOf<UAnimInstance> FirstPersonToolAnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable Tool Base")
	TSubclassOf<UAnimInstance> ThirdPersonToolAnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable Tool Base")
	TObjectPtr<USkeletalMeshComponent> ToolMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable Tool Base")
	TObjectPtr<AAdventureCharacter> OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable Tool Base")
	TObjectPtr<UInputMappingContext> ToolMappingContext;

	AEquippableToolBase();

	UFUNCTION()
	virtual void Use();

	UFUNCTION()
	virtual void BindInputAction(const UInputAction* ActionToBind);
};

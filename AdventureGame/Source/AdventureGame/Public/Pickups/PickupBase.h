// Pickups/PickupBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "AdventureCharacter.h"
#include "PickupBase.generated.h"

class UItemDefinition;

UCLASS(BlueprintType, Blueprintable, meta = (PrioritizeCategories = "Pickup"))
class ADVENTUREGAME_API APickupBase : public AActor
{
	GENERATED_BODY()

	// base 
protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	// runs whenever a property on this object is changed in the editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	// current
public:
	APickupBase();

	void InitializePickup();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Pickup Base | Item Table")
	TSoftObjectPtr<UDataTable> PickupDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup Base | Item Table")
	FName PickupItemID;

	UPROPERTY(VisibleAnywhere, Category = "Pickup Base | Reference Item")
	TObjectPtr<UItemDefinition> ReferenceItem;

	UPROPERTY(VisibleAnywhere, Category = "Pickup Base | Mesh")
	TObjectPtr<UStaticMeshComponent> PickupMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Base | Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Base | Respawn")
	bool bShouldRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Base | Respawn")
	float RespawnTime = 4.f;

	FTimerHandle RespawnTimerHandle;

	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};

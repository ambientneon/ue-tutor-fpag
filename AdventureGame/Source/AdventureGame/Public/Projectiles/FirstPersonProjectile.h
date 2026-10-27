// Projectiles/FirstPersonProjectile.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstPersonProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API AFirstPersonProjectile : public AActor
{
	GENERATED_BODY()

	// base 
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	
	// current
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "First Person Projectile | Mesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "First Person Projectile | Physics")
	float PhysicsForce = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "First Person Projectile | Lifespan")
	float ProjectileLifespan = 5.f;

	AFirstPersonProjectile();

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& HitResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "First Person Projectile | Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "First Person Projectile | Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

private:
	void InitializeCollisionsComponent();
	void InitializeMeshComponent();
	void InitializeMovementComponent();
};

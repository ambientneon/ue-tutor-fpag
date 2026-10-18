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
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile | Mesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile | Physics")
	float PhysicsForce = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile | Lifespan")
	float ProjectileLifespan = 5.f;

	
	AFirstPersonProjectile();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& HitResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile | Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile | Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;


	virtual void BeginPlay() override;

private:
	void InitializeCollisionsComponent();
	void InitializeMeshComponent();
	void InitializeMovementComponent();
};

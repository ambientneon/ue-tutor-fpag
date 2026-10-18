#include "Projectiles/FirstPersonProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#pragma region Public
AFirstPersonProjectile::AFirstPersonProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeCollisionsComponent();
	InitializeMeshComponent();
	InitializeMovementComponent();

	InitialLifeSpan = ProjectileLifespan;
}

void AFirstPersonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstPersonProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& HitResult
)
{
	if (FVector::DotProduct(HitResult.ImpactNormal, FVector::UpVector) > 0.7f)
	{
		FRotator Flat = GetActorRotation();
		Flat.Pitch = 0.f;
		Flat.Roll = 0.f;
		SetActorRotation(Flat);

		return;
	}

	if (!OtherActor || OtherActor == this) { return; }
	if (!OtherComp || !OtherComp->IsSimulatingPhysics()) { return; }

	OtherComp->AddImpulseAtLocation(GetVelocity() * PhysicsForce, GetActorLocation());
	Destroy();
}
#pragma endregion

#pragma region Protected
void AFirstPersonProjectile::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion

#pragma region Private
void AFirstPersonProjectile::InitializeCollisionsComponent()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	if (!ensure(CollisionComponent)) { return; }

	CollisionComponent->InitSphereRadius(5.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFirstPersonProjectile::OnHit);

	RootComponent = CollisionComponent;
}

void AFirstPersonProjectile::InitializeMeshComponent()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	if (!ensure(ProjectileMesh)) { return; }
	if (!ensure(CollisionComponent)) { return; }

	ProjectileMesh->SetupAttachment(CollisionComponent);
}

void AFirstPersonProjectile::InitializeMovementComponent()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	if (!ensure(ProjectileMovement)) { return; }
	if (!ensure(CollisionComponent)) { return; }

	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.2f;
	ProjectileMovement->Friction = 0.8f;
}
#pragma endregion

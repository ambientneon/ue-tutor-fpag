#include "Pickups/PickupBase.h"
#include "Data/ItemDefinition.h"
#include "Data/ItemData.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	if (!ensure(PickupMeshComponent)) { return; }

	SetRootComponent(PickupMeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (!ensure(SphereComponent)) { return; }

	SphereComponent->SetupAttachment(PickupMeshComponent);
	SphereComponent->SetSphereRadius(32.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);

	InitializePickup();
}

void APickupBase::InitializePickup()
{
	if (!ensure(PickupDataTable)) { return; }

	const FSoftObjectPath TablePath = PickupDataTable.ToSoftObjectPath();
	if (!ensure(!TablePath.IsNull() && !PickupItemID.IsNone())) { return; }

	UDataTable* LoadedDataTable = PickupDataTable.IsValid()
		? PickupDataTable.Get()
		: PickupDataTable.LoadSynchronous();
	if (!ensure(LoadedDataTable)) { return; }

	const FItemData* ItemDataRow = LoadedDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());
	if (!ensure(ItemDataRow)) { return; }

	UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase.IsValid()
		? ItemDataRow->ItemBase.Get()
		: ItemDataRow->ItemBase.LoadSynchronous();
	if (!ensure(TempItemDefinition)) { return; }

	ReferenceItem = NewObject<UItemDefinition>(this);
	ReferenceItem->ID = TempItemDefinition->ID;
	ReferenceItem->ItemType = TempItemDefinition->ItemType;
	ReferenceItem->ItemText = TempItemDefinition->ItemText;
	ReferenceItem->WorldMesh = TempItemDefinition->WorldMesh;

	UStaticMesh* LoadedMesh = TempItemDefinition->WorldMesh.IsValid()
		? TempItemDefinition->WorldMesh.Get()
		: TempItemDefinition->WorldMesh.LoadSynchronous();
	if (!ensure(LoadedMesh)) { return; }

	PickupMeshComponent->SetStaticMesh(LoadedMesh);
	PickupMeshComponent->SetVisibility(true);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APickupBase::OnSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Attempting a pickup collision"));

	AAdventureCharacter* Character = Cast<AAdventureCharacter>(OtherActor);
	if (!Character) { return; }
	
	PickupMeshComponent->SetVisibility(false);
	PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (bShouldRespawn)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBase::InitializePickup, RespawnTime, false);
	}
}

#if WITH_EDITOR
void APickupBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickupBase, PickupDataTable) ||
		ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickupBase, PickupItemID))
	{
		InitializePickup();
	}
}
#endif
#include "Pickups/PickupBase.h"
#include "Data/ItemDefinition.h"
#include "Data/ItemData.h"

#pragma region Public
APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("PICKUP[%s] BeginPlay"), *GetName());

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

void APickupBase::InitializePickup()
{
	if (!ensureMsgf(!PickupDataTable.IsNull(), TEXT("Pickup[%s]: DataTable not set"), *GetName())) { return; }
	if (!ensureMsgf(!PickupItemID.IsNone(), TEXT("Pickup[%s]: PickupItemID is None"), *GetName())) { return; }

	UDataTable* LoadedDataTable = PickupDataTable.IsValid()
		? PickupDataTable.Get()
		: PickupDataTable.LoadSynchronous();
	if (!ensureMsgf(LoadedDataTable, TEXT("Pickup[%s]: failed to load DataTable"), *GetName())) { return; }

	const FItemData* ItemDataRow = LoadedDataTable->FindRow<FItemData>(PickupItemID, TEXT("InitializePickup"));
	if (!ensureMsgf(ItemDataRow, TEXT("Pickup[%s]: row '%s' not found"), *GetName(), *PickupItemID.ToString())) { return; }

	UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase.IsValid()
		? ItemDataRow->ItemBase.Get()
		: ItemDataRow->ItemBase.LoadSynchronous();
	if (!ensureMsgf(TempItemDefinition, TEXT("Pickup[%s]: ItemBase load failed"), *GetName())) { return; }
	
	ReferenceItem = TempItemDefinition->CreateItemCopy(GetTransientPackage());
	if (!ensureMsgf(ReferenceItem, TEXT("Pickup[%s]: RefenceItem create failed"), *GetName())) { return; }

	UStaticMesh* LoadedMesh = TempItemDefinition->WorldMesh.IsValid()
		? TempItemDefinition->WorldMesh.Get()
		: TempItemDefinition->WorldMesh.LoadSynchronous();
	if (!ensureMsgf(LoadedMesh, TEXT("Pickup[%s]: WorldMesh load failed"), *GetName())) { return; }

	PickupMeshComponent->SetStaticMesh(LoadedMesh);
	PickupMeshComponent->SetVisibility(true);
	PickupMeshComponent->SetHiddenInGame(false);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
#pragma endregion

#pragma region Protected
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);

	InitializePickup();
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
	if (!Character || !ReferenceItem) { return; }

	Character->GiveItem(ReferenceItem);

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
#pragma endregion
